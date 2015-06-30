<?php
/**
 * Implements form_hook.
 **/
function livi_users_add_form($form, &$form_state){
  $form ['username'] = array(
    '#title' => 'Nombre de usuario',
    '#type' => 'textfield',
    '#placeholder' => t('Nombre de usuario'), 
    '#attributes' => array('placeholder' => t('Nombre de usuario')), 
    '#required' => TRUE,
  );

  $form ['email'] = array(
    '#title' => 'Email',
    '#type' => 'textfield',
    '#placeholder' => t('Email'), 
    '#attributes' => array('placeholder' => t('Email')), 
    '#required' => TRUE,
  );

  $form ['tel_label'] = array(
    '#type' => 'markup',
    '#markup' => '<h3>Telefono Celular</h3>', 
  );

  $form ['tel_pref'] = array(
    '#title' => 'Clave Telefono',
    '#type' => 'textfield',
    '#placeholder' => t('311'), 
    '#attributes' => array('placeholder' => t('311')), 
    '#required' => TRUE,
  );

  $form ['tel_num'] = array(
    '#title' => 'Numero de Telefono',
    '#type' => 'textfield',
    '#placeholder' => t('1232233'), 
    '#attributes' => array('placeholder' => t('1232233')), 
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Enviar'),
  );

  return $form;
}

function livi_users_add_form_submit($form,&$form_state) {

  if (isset($form_state['values']['username'])){
    $username = $form_state['values']['username'];
  }

  if (isset($form_state['values']['email'])){
    $email = $form_state['values']['email'];
  }

  if (isset($form_state['values']['tel_pref']) && isset($form_state['values']['tel_num'])){
    $tel = intval($form_state['values']['tel_pref'] . $form_state['values']['tel_num']);
  }

  if (user_load_by_name($username)) {
    drupal_set_message(t('El nombre de usuario que esta intentando usar ya esta registrado'), 'error', FALSE);

    return false;
  }

  if (user_load_by_mail($email)) {
    drupal_set_message(t('El correo que esta intentando usar ya esta registrado'), 'error', FALSE);

    return false;
  }

  if (livi_users_load_by_tel($tel)) {
    drupal_set_message(t('El telefono que esta intentando usar ya esta registrado'), 'error', FALSE);

    return false;
  }
  // Set Operador role.
  $roles = array(
    2 => 'authenticated user', 
    5 => 'miembro', 
  );

  // Get the user info.
  $nuser = array(
    'name' => $username, 
    'roles' => $roles,
    'mail' => $email,
    'init' => $email, 
    'field_celular' => array(LANGUAGE_NONE => array(array('value' => $tel))),
    'status' => 1, 
    'access' => REQUEST_TIME, 
  );

  // Save the user.
  $user =  user_save(null, $nuser);

  if (!$user){
    drupal_set_message(t('Ocurrio un error registrando el usuario'), 'error', FALSE);
    return false;
  }

  $op = 'register_no_approval_required';

  _user_mail_notify($op, $user, $language = NULL);

  drupal_set_message(t('El usuario ha sido registrado'), 'status', FALSE);

  return true;

}