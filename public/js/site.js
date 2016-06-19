$(document).ready(function() {
    updateTotal();

    $(document).on('click', '.select-ctrl', function() {
        var target = $(this).attr('select-target');

        if (target && $(target).length) {
            $(target).select();
        }
    });

    $(document).on('click', 'ga-event', function() {
        var $element = $(this);
        var category = $element.attr('data-ga-category') || 'Element';
        var action = $element.attr('data-ga-action') || 'Event';
        var label = $element.attr('data-ga-label') || 'None';
        var value = $element.attr('data-ga-value') || 0;

        if (typeof ga === 'function') {
            ga('send', 'event', category, action, label, value);
        }
    });

    $('form').on('submit', function() {
        $('.msgs').empty();

        var data = {
            action: $(this).attr('data-action') ? $(this).attr('data-action') : 'submit'
        };

        $(this).find('input.form-input').each(function() {
            data[$(this).attr('name')] = $(this).val();
        });

        $.ajax({
            url: 'ajax.php',
            type: 'POST',
            dataType: 'json',
            data: data,
            success: function(response) {
                if (response.success) {
                    if (typeof ga === 'function') {
                        ga('send', 'event', data.action, JSON.stringify(data));
                    }

                    if (data.action == 'generate' && response.cmd) {
                        $('.result').addClass('active');
                        $('#cmd').val(response.cmd);
                        $('#instructions-cmd').text(' $ '+response.cmd);

                        if (response.hits) {
                            $('.msgs').append('<p class="bg-primary">The socket associated to this email has been opened ' + response.hits + ' time(s)</p>');
                        }
                    } else if (data.action == 'unsub') {
                        $('.msgs').append('<p class="bg-primary">You have been successfully removed from the Say Socket database</p>');
                        $('.unsub-info').hide();
                    }
                } else if (response.errors) {
                    $.each(response.errors, function(i, msg) {
                        $('.msgs').append('<p class="bg-danger">' + msg + '</p>');
                    });
                }
            },
            failure: function (response) {
                console.log(response);
            }
        });

        return false;
    });
});

function updateTotal() {
    $.ajax({
        url: 'ajax.php',
        type: 'POST',
        dataType: 'json',
        data: {
            action: 'total'
        },
        success: function(response) {
            if (response.success && response.total) {
                $('.total').text(response.total);
            }
        },
        failure: function(response) {
            console.log(response);
        }
    });

    setTimeout(function() {
        updateTotal();
    }, 5000);
}
