(function ($) {
    Drupal.behaviors.refreshTagging = {
        attach:function (context, settings) {
						$('input.tagging-widget-input').tagging();
        }
    };
})(jQuery);