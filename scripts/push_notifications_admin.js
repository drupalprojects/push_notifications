(function ($) {
  $(document).ready(function(){
    // Only show options for C2DM, GCM or FCM.
  	$('input#edit-push-notifications-google-type-0').click(function(e) {
      $('fieldset#edit-c2dm-credentials').show();
      $('fieldset#edit-gcm-credentials').hide();
      $('fieldset#edit-fcm-credentials').hide();
  	});
    
  	$('input#edit-push-notifications-google-type-1').click(function(e) {
      $('fieldset#edit-c2dm-credentials').hide();
      $('fieldset#edit-gcm-credentials').show();
      $('fieldset#edit-fcm-credentials').hide();
    });

    $('input#edit-push-notifications-google-type-2').click(function(e) {
      $('fieldset#edit-c2dm-credentials').hide();
      $('fieldset#edit-gcm-credentials').hide();
      $('fieldset#edit-fcm-credentials').show();
    });

  });  
})(jQuery);