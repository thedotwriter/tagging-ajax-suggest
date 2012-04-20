(function ($) {
  Drupal.behaviors.refresh_d6 = function() {
    var obj = {
      attach: function() {
        //We need to reset the state of each tagging field so that Drupal.behaviors.tagging_d6 can do its job well.
			$('input.tagging-widget-input').removeClass('tagging-processed');
      }
    };
    obj.attach();
  };
})(jQuery);