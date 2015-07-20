$(document).ready(function() {
    $(document).on('click','.select-ctrl', function() {
        var target = $(this).attr('select-target');

        if (target && $(target).length) {
            $(target).select();
        }
    });

    $('form').on('submit', function() {
        $.ajax({
            url: 'ajax.php',
            type: 'POST',
            dataType: 'json',
            data: {
                email: $('#email').val()
            },
            success: function(response) {
                if (response.success && response.cmd) {
                    $('.result').addClass('active');

                    $('#cmd').val(response.cmd);
                    $('#instructions-cmd').text(' $ '+response.cmd);
                } else if (response.errors) {
                    $('.msgs').find('.msgs-wrap').empty();

                    $.each(response.errors, function(i, msg) {
                        $('.msgs').find('.msgs-wrap').append('<p class="bg-danger">' + msg + '</p>');
                    });
                }
            },
            failure: function (response) {
                console.log(response);
            }
        });

        return false;
    })
});