<?php

class conferencetabs extends tabs
{
    var $base= "";

    function __construct($config, $data, $dn, $category)
    {
        tabs::__construct($config, $data, $dn,$category);
        $this->base= $this->by_object['conference']->base; 

        /* Add references/acls/snapshots */
        $this->addSpecialTabs();
    }

    function check($ignore_account= FALSE)
    {
        return (tabs::check(TRUE));
    }


    function save($ignore_account= FALSE)
    {
        $baseobject= $this->by_object['conference'];
        $cn      = preg_replace('/,/', '\,', $baseobject->cn);
        $cn      = preg_replace('/"/', '\"', $cn);
        $new_dn= @LDAP::convert('cn='.$cn.','.get_ou("conference", "phoneConferenceRDN").$baseobject->base);

        if(strtolower($this->dn)==strtolower($new_dn)){
            $this->dn=$new_dn;
        }

        if($this->dn != $new_dn && $this->dn != "new"){
            $baseobject->recursive_move($this->dn, $new_dn);
        }
        $this->dn= $new_dn;

        tabs::save(TRUE);
    }

}

?>
