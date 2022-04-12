# 5.6-fpm-stretch
# 5.6-fpm-jessie

FROM php:7.4-fpm-buster

ENV APP_DIR /var/www/app
ENV APP_USER www-data

ENV NGINX_PATH=/etc/nginx

RUN mkdir -p $APP_DIR

# Set working directory
WORKDIR $APP_DIR

# Install dependencies
# RUN apt-get update && apt-get install -y \
#     zlib1g-dev \
#     libonig-dev \
#     build-essential \
#     default-mysql-client \
#     libxml2-dev \
#     libpng-dev \
#     libjpeg62-turbo-dev \
#     libfreetype6-dev \
#     libdbi-perl \
#     libjson-perl \
#     libswitch-perl \
#     libdatetime-perl \
#     locales \
#     zip \
#     jpegoptim optipng pngquant gifsicle libonig-dev \
#     vim \
#     xvfb \
#     unzip \
#     git \
#     curl \
#     cron \
#     nginx \
#     supervisor \
#     nodejs \
#     npm

# Install apt requirements & dependencies
RUN apt-get update && apt-get install -y \
    build-essential default-mysql-client \
    libpng-dev libjpeg62-turbo-dev libfreetype6-dev libzip-dev libssl-dev libbz2-dev libicu-dev libpq-dev libmcrypt-dev libonig-dev \
    locales zip jpegoptim optipng pngquant gifsicle vim xvfb unzip git curl cron nginx supervisor zlib1g-dev \
    #
    # Install imagick, mcrypt, and redis using pecl
    # && pecl install imagick-3.4.4 mcrypt-1.0.4 redis \
    #
    # Clear apt cache
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Install composer
# RUN curl -sS https://getcomposer.org/installer | php -- --install-dir=/usr/local/bin --filename=composer --version=1.10.16 \
#     && curl -Lso /tmp/wkhtmltopdf.deb https://github.com/wkhtmltopdf/wkhtmltopdf/releases/download/0.12.5/wkhtmltox_0.12.5-1.stretch_amd64.deb \
#     && apt-get install -y /tmp/wkhtmltopdf.deb \
#     && curl -Lso /usr/local/bin/mhsendmail https://github.com/mailhog/mhsendmail/releases/download/v0.2.0/mhsendmail_linux_amd64 \
#     && chmod +x /usr/local/bin/mhsendmail

RUN curl -Lso /usr/local/bin/mhsendmail https://github.com/mailhog/mhsendmail/releases/download/v0.2.0/mhsendmail_linux_amd64 \
    && chmod +x /usr/local/bin/mhsendmail

# Clear cache
RUN apt-get clean && rm -rf /var/lib/apt/lists/*

# Install extensions
RUN docker-php-ext-install pdo_mysql pdo_pgsql mbstring zip exif pcntl bcmath bz2 ftp gettext opcache shmop sockets sysvmsg sysvsem sysvshm iconv intl \
    && docker-php-ext-configure gd --with-freetype --with-jpeg \
    && docker-php-ext-install gd
    # && docker-php-ext-enable imagick mcrypt redis

RUN rm $NGINX_PATH/sites-enabled/*

# RUN mkdir -p /etc/cron.d \
#     && touch /root/env.sh \
#     && touch /var/log/cron.log \
#     && chown www-data:www-data /var/log/cron.log

# COPY etc/ssh /root/.ssh

COPY etc/nginx $NGINX_PATH
# COPY etc/cron.d/* /etc/cron.d/
COPY etc/php/* /usr/local/etc/php/
COPY etc/php-fpm.d/* /usr/local/etc/php-fpm.d/
COPY etc/supervisord/* /etc/supervisor/conf.d/

# RUN chmod 0644 /etc/cron.d/* \
#     && crontab /etc/cron.d/scheduled-jobs.cron \
#     && ln -s $NGINX_PATH/sites-available/www.conf $NGINX_PATH/sites-enabled/www.conf \
#     && nginx -t

RUN ln -s $NGINX_PATH/sites-available/www.conf $NGINX_PATH/sites-enabled/www.conf && nginx -t

# Copy existing application directory contents
COPY . .

# Expose port 80 and start php-fpm server
EXPOSE 80

ENTRYPOINT ["./docker-entrypoint.sh"]

# CMD ["php-fpm"]
CMD [ "/usr/bin/supervisord", "-c", "/etc/supervisor/conf.d/supervisord.conf" ]
