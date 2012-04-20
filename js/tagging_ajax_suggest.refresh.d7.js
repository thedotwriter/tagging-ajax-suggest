(function ($) {
	Drupal.behaviors.refresh_d7 = {
		attach:function (context, settings) {
			//We need to reset the state of system in the case were the JS would be reload after an AJAX request.
			$('input.tagging-widget-input').removeClass('tagging-processed');
		}
	};
})(jQuery);