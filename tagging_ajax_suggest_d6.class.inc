<?php

class tagging_ajax_suggest_d6 extends tagging_ajax_suggest_base 
{
  /**
   * Define the callback path
   *
   * @see tagging_ajax_suggest_menu()
   *
   * @return array
   */
  public function hook_menu() 
  {
    $items = array();

    $items['tagging_ajax_suggest/callback'] = array(
      'page callback' => 'tagging_ajax_suggest_form_callback',
      'access callback' => TRUE,
      'type' => MENU_CALLBACK,
    );

    return $items;
  }

  /**
   * Build and render the tagging field with suggestions
   */
  public function tagging_ajax_suggest_form_callback() 
  {
    $data = $this->tagging_ajax_suggest_callback_helper();
    
    $form = $data['form'];
    $node = $data['form_state']['post'];

    // TODO: Add support for multiple tagging field on one node. At this point, the module just 
    // pick data from the first one. To change that, it will be needed to know wich "Suggest tag" 
    // button has been clicked.
    $element = $form['taxonomy']['tags'][1];

    // Load suggestions
    $suggestions = _tagging_get_suggestions($element['#vid'], (object) $node);
    $element['#suggestions'] = $suggestions;

    // Include the results of any drupal_set_message() calls that
    // may have occurred.
    $output = tagging_base::instance()->theme('status_messages', array());
    
    $output .= tagging_base::instance()->theme('tagging_widget', array('element' => $element));

    // Output the results and exit.
    drupal_json(array('status' => TRUE, 'data' => $output));
    exit();
  }
  
  /**
   * Does the very standard things that must be done in a callback on D6.
   *
   * @return array Contains $form and $form_state values
   */
  public function tagging_ajax_suggest_callback_helper() 
  {
    //Generate error if not loaded.
    module_load_include('inc', 'node', 'node.pages');
    
    $form_state = array('storage' => NULL, 'submitted' => FALSE);
    $form_build_id = $_POST['form_build_id'];
    $form = form_get_cache($form_build_id, $form_state);
    $args = $form['#parameters'];
    $form_id = array_shift($args);
    $form_state['post'] = $form['#post'] = $_POST;
    // Enable the submit/validate handlers to determine whether AHAH-submittted.
    $form_state['ahah_submission'] = TRUE;
    $form['#programmed'] = $form['#redirect'] = FALSE;
    drupal_process_form($form_id, $form, $form_state);
    $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);
    
    return array('form' => $form, 'form_state' => $form_state);
  }

}