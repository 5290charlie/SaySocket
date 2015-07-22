$(document).ready(function() {
    updateTotal();

    $(document).on('click','.select-ctrl', function() {
        var target = $(this).attr('select-target');

        if (target && $(target).length) {
            $(target).select();
        }
    });

    $('form').on('submit', function() {
        $('.msgs').empty();

        $.ajax({
            url: 'ajax.php',
            type: 'POST',
            dataType: 'json',
            data: {
                action: 'generate',
                email: $('#email').val()
            },
            success: function(response) {
                if (response.success && response.cmd) {
                    if (typeof ga === 'function') {
                        ga('send', 'event', 'generated', $('#email').val());
                    }

                    $('.result').addClass('active');
                    $('#cmd').val(response.cmd);
                    $('#instructions-cmd').text(' $ '+response.cmd);

                    if (response.hits) {
                        $('.msgs').append('<p class="bg-primary">The socket associated to this email has been opened ' + response.hits + ' time(s)</p>');
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

