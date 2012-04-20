<?php

class tagging_ajax_suggest_d7 extends tagging_ajax_suggest_base 
{
  /**
   * Add the "Suggest tags" button and set AJAX callback
   *
   * @see tagging_ajax_suggest_field_widget_tagging_taxonomy_autocomplete_form_alter()
   */
	public function hook_field_widget_tagging_taxonomy_autocomplete_form_alter(&$element, &$form_state, $context) 
  {
		$element['suggestions'] += array(
      '#prefix' => '<div id="tagging_ajax_suggest">',
      '#suffix' => '</div>',
    );

    $element['refresh'] = array(
      '#type' => 'container',
    );

    $element['refresh']['button'] = array(
      '#type' => 'submit',
      '#value' => t('Suggest tags'),
      '#ajax' => array(
        'callback' => 'tagging_ajax_suggest_callback',
        'wrapper' => 'tagging_ajax_suggest',
      ),
    );
    
    $storage = array(
      'machine_name' => $context['field']['settings']['allowed_values'][0]['vocabulary'],
      'field_name' => $context['field']['field_name'],
    );
    
    // Pass some values for the callback function  
    variable_set('storage', $storage);
    // I need to put values in here instead of an "hidden" field in the form element itself since it would be
    // impossible to get the stored data if I don't know the field_name in the first place.
	}

}