<?php

class phonetabs extends tabs
{

  function __construct($config, $data, $dn,$category)
  {
    tabs::__construct($config, $data, $dn,$category);

    /* Add references/acls/snapshots */
    $this->addSpecialTabs();
  }

  function save_object($save_current= FALSE)
  {
    tabs::save_object($save_current);

    $baseobject = $this->by_object['phoneGeneric'];
    $baseobject->netConfigDNS->cn= $baseobject->cn;
  }


  function save($ignore_account= FALSE)
  {
    /* Check for new 'dn', in order to propagate the
       'dn' to all plugins */
    $baseobject= $this->by_object['phoneGeneric'];
    $cn      = preg_replace('/,/', '\,', $baseobject->cn);
    $cn      = preg_replace('/"/', '\"', $cn);
    $this->dn= "cn={$cn},".get_ou("phoneGeneric", "phoneRDN").$baseobject->base;
    $baseobject->dn= $this->dn;

    foreach ($this->by_object as $key => $obj){
      $this->by_object[$key]->dn= $this->dn;
    }

    tabs::save(TRUE);
  }

}


?>
