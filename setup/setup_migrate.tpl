<div>
    <div class='default'>

	{if $method == "default"}
			<p>{t}During the LDAP inspection, we're going to check for several common pitfalls that may occur when migration to GOsa base LDAP administration. You may want to fix the problems below, in order to provide smooth services.{/t}
			</p>

			{foreach from=$checks item=val key=key}
				<div style='width:98%; padding:4px; background-color:{cycle values="#F0F0F0, #FFF"}'>

			{if $checks.$key.ERROR_MSG}
                                <!-- Add ability to display info popup -->
                                <div class='step2_entry_container_info'>
                        {else}
                                <!-- Normal entry everything is fine -->
                                <div class='step2_entry_container'>
                        {/if}
				<div class='step2_entry_name'><b>{$checks.$key.TITLE}</b></div>
				<div class='step2_entry_status'>
				{if $checks.$key.STATUS}
					<div class='step2_successful'>{$checks.$key.STATUS_MSG}</div>
				{else}
					<div class='step2_failed'>{$checks.$key.STATUS_MSG}</div>
				{/if}
				</div>
					{if $checks.$key.ERROR_MSG}
						{$checks.$key.ERROR_MSG}
					{/if}
				</div>
				</div>
			{/foreach}
		<br>
		<input type='submit' name='reload' value='{t}Check again{/t}'>

		{elseif $method == "outside_winstations"}

			<h2>{t}Move windows workstations into a valid windows workstation department{/t}</h2>

			{t}This dialog allows you to move the displayed windows workstations into a valid department{/t}
			<br>
			{t}Be careful with this tool, there may be references pointing to this workstations that can't be migrated.{/t}
			<br>
			<br>	

			{foreach from=$outside_winstations item=val key=key}
				{if $outside_winstations.$key.selected}
					<input type='checkbox' name='select_winstation_{$key}' checked>
				{else}
					<input type='checkbox' name='select_winstation_{$key}'>
				{/if}

				&nbsp;{$outside_winstations.$key.dn}
				{if $outside_winstations.$key.ldif != ""}
                    <div class="step2_entry_container_info" id="sol_8">
						<div style='padding-left:20px;'>
							<pre>
								{$outside_winstations.$key.ldif}
							</pre>
						</div>
					</div>
				{/if}
				<br>
			{/foreach}

			<p>
			<b>{t}Move selected windows workstations into the following GOsa department{/t} : </b>
			<select name='move_winstation_to'>
				{html_options options=$ous}
			</select>
			<br>
			<input type='submit' name='outside_winstations_dialog_perform' value='{t}Move selected workstations{/t}'>
			<input type='submit' name='outside_winstations_dialog_whats_done' value='{t}What will be done here{/t}'>
			</p>
				

			<p class='seperator'>&nbsp;</p>	
			<div style='width:100%; text-align:right; padding:5px;'>
				<input type='submit' name='outside_winstations_dialog_cancel' value='{t}Close{/t}'>
			</div>
		

		{elseif $method == "outside_groups"}

			<h2>{t}Move groups into configured group tree{/t}</h2>

                        <p>
                        {t}This dialog allows moving a couple of groups to the configured group tree. Doing this may straighten your LDAP service.{/t}
                        </p>
                        <p style='color:red'>
                        {t}Be careful with this option! There may be references pointing to these groups. The GOsa setup can't migrate references, so you may want to cancel the migration in this case in this case.{/t}
                        </p>
			<p>
			{t}Move selected groups into this group tree{/t}: 
			<select name='move_group_to'>
				{html_options options=$ous}
			</select>
			</p>

			{foreach from=$outside_groups item=val key=key}
				{if $outside_groups.$key.selected}
					<input type='checkbox' name='select_group_{$key}' checked>
				{else}
					<input type='checkbox' name='select_group_{$key}'>
				{/if}

				&nbsp;{$outside_groups.$key.dn}
				{if $outside_groups.$key.ldif != "" && $group_details}
                      <div class="step2_entry_container_info" id="sol_8">
<div style='padding-left:20px;'>
<pre>
{$outside_groups.$key.ldif}
</pre>
</div>
</div>
				{/if}
				<br>
			{/foreach}

			<p>
                        {if $group_details}
                        <input type='submit' name='outside_groups_dialog_refresh' value='{t}Hide changes{/t}'>
                        {else}
                        <input type='submit' name='outside_groups_dialog_whats_done' value='{t}Show changes{/t}'>
                        {/if}
			</p>

			<p class='seperator'>&nbsp;</p>	
			<div style='width:99%; text-align:right; padding:5px;'>
				<input type='submit' name='outside_groups_dialog_perform' value='{t}Apply{/t}'>
				&nbsp;
				<input type='submit' name='outside_groups_dialog_cancel' value='{t}Cancel{/t}'>
			</div>
		
		{elseif $method == "outside_users"}

			<h2>{t}Move users into configured user tree{/t}</h2>
			<p>
			{t}This dialog allows moving a couple of users to the configured user tree. Doing this may straighten your LDAP service.{/t}
			</p>
			<p style='color:red'>
			{t}Be careful with this option! There may be references pointing to these users. The GOsa setup can't migrate references, so you may want to cancel the migration in this case.{/t}
			</p>	
			<p>
			{t}Move selected users into this people tree{/t}: 
			<select name='move_user_to'>
				{html_options options=$ous}
			</select>
			</p>
			{foreach from=$outside_users item=val key=key}
				{if $outside_users.$key.selected}
					<input type='checkbox' name='select_user_{$key}' checked>
				{else}
					<input type='checkbox' name='select_user_{$key}'>
				{/if}

				&nbsp;{$outside_users.$key.dn}
				{if $outside_users.$key.ldif != "" && $user_details}
                      <div class="step2_entry_container_info" id="sol_8">
<div style='padding-left:20px;'>
<pre>
{$outside_users.$key.ldif}
</pre>
</div>
</div>
				{/if}
				<br>
			{/foreach}
			<br>
			{if $user_details}
			<input type='submit' name='outside_users_dialog_refresh' value='{t}Hide changes{/t}'>
                        {else}
			<input type='submit' name='outside_users_dialog_whats_done' value='{t}Show changes{/t}'>
			{/if}

			<p class='seperator'>&nbsp;</p>	
			<div style='width:99%; text-align:right; padding:5px;'>
				<input type='submit' name='outside_users_dialog_perform' value='{t}Apply{/t}'>
				&nbsp;
				<input type='submit' name='outside_users_dialog_cancel' value='{t}Cancel{/t}'>
			</div>
		

		{elseif $method == "create_acls"}

		{if $acl_create_selected != "" && $what_will_be_done_now!=""}
			<div>
<pre>
{$what_will_be_done_now}
</pre>
			</div>		
			<input type='submit' name='create_acls_create_confirmed' value='{t}Next{/t}'>
			<input type='submit' name='create_acls_create_abort' value='{t}Abort{/t}'>
		{else}
			<h2>{t}Create a new GOsa administrator account{/t}</h2>
	
			<p>
			{t}This dialog will automatically add a new super administrator to your LDAP tree.{/t}
			</p>
			<table>
				<tr>
					<td>
						{t}Name{/t}:&nbsp;
					</td>
					<td>
						<i>System administrator</i>
					</td>
				<tr>
				<tr>
					<td>
						{t}User ID{/t}:&nbsp;
					</td>
					<td>
						<i>admin</i>
					</td>
				<tr>
				</tr>
					<td>
						{t}Password{/t}:&nbsp;
					</td>
					<td>
						<input type='password' value='{$new_user_password}' name='new_user_password'><br>
					</td>
				</tr>
				</tr>
					<td>
						{t}Password (again){/t}:&nbsp;
					</td>
					<td>
						<input type='password' value='{$new_user_password2}' name='new_user_password2'><br>
					</td>
				</tr>
			</table>
			
			{if $users_cnt != 0 || $groups_cnt != 0}
			
			<h2>{t}Assign super administrator permissions to an existing user or group{/t}</h2>
			<p>{t}To grant administrative permissions to a user or a group, select an object and choose 'Assign'.{/t}</p>
			<select name='acl_create_type' onChange='document.mainform.submit();' >
				{if $type == "user"}
				<option value='group'>{t}Group{/t}</option>
				<option selected value='user'>{t}User{/t}</option>
				{else}
				<option selected value='group'>{t}Group{/t}</option>
				<option value='user'>{t}User{/t}</option>
				{/if}
			</select>
			<select name='create_acls_selected' size="12" style='width:100%;'>
				{if $type == "user"}
					{html_options options=$users selected=$acl_create_selected}
				{else}
					{html_options options=$groups selected=$acl_create_selected}
				{/if}
			</select>
			{/if}
		{/if}


			<p class='seperator'>&nbsp;</p>	

			<div style='width:99%; text-align:right; padding:5px;'>
				{if $users_cnt != 0 || $groups_cnt != 0}
				<input type='submit' name='create_acls_create' value='{t}Apply{/t}'>
				{else}
				<input type='submit' name='create_admin_user' value='{t}Apply{/t}'>	
				{/if}
				&nbsp;
				<input type='submit' name='create_acls_cancel' value='{t}Cancel{/t}'>
			</div>
		

		{elseif $method == "migrate_deps"}
	
			<h2>Department migration</h2>

			<p>{t}The listed departments are currenlty invisble in the GOsa user interface. If you want to change this for a couple of entries, select them and use the migrate button below.{/t}</p>
			<p>{t}If you want to know what will be done when migrating the selected entries, use the 'Show changes' button to see the LDIF.{/t}</p>
					
			{foreach from=$deps_to_migrate item=val key=key}

				{if $deps_to_migrate.$key.checked}
					<input type='checkbox' name='migrate_{$key}' checked>
					{$deps_to_migrate.$key.dn}
					{if $deps_to_migrate.$key.after != ""}
						<div class="step2_entry_container_info" id="sol_8">

{t}Current{/t}
<div style='padding-left:20px;'>
<pre>
dn: {$deps_to_migrate.$key.dn}
{$deps_to_migrate.$key.before}
</pre>
</div>
{t}After migration{/t}
<div style='padding-left:20px;'>
<pre>
dn: {$deps_to_migrate.$key.dn}
{$deps_to_migrate.$key.after}
</pre>
</div>
						</div>
					{/if}
				{else}
					<input type='checkbox' name='migrate_{$key}'>
					{$deps_to_migrate.$key.dn}
				{/if}
				

			{/foreach}

			<br>
			{if $deps_details}
			<input type='submit' name='deps_visible_migrate_refresh' value='{t}Hide changes{/t}'>
			{else}
			<input type='submit' name='deps_visible_migrate_whatsdone' value='{t}Show changes{/t}'>
			{/if}

			<p class='seperator'>&nbsp;</p>	

			<div style='width:99%; text-align:right; padding:5px;'>
				<input type='submit' name='deps_visible_migrate_migrate' value='{t}Apply{/t}'>
				&nbsp;
				<input type='submit' name='deps_visible_migrate_close' value='{t}Cancel{/t}'>
			</div>
		{elseif $method == "migrate_users"}
	
			<h2>User migration</h2>

			<p>{t}The listed users are currenlty invisble in the GOsa user interface. If you want to change this for a couple of users, just select them and use the 'Migrate' button below.{/t}</p>
			<p>{t}If you want to know what will be done when migrating the selected entries, use the 'Show changes' button to see the LDIF.{/t}</p>
			{foreach from=$users_to_migrate item=val key=key}

				{if $users_to_migrate.$key.checked}
					<input type='checkbox' name='migrate_{$key}' checked>
					{$users_to_migrate.$key.dn}
					{if $users_to_migrate.$key.after != ""}
						<div class="step2_entry_container_info" id="sol_8">

{t}Current{/t}
<div style='padding-left:20px;'>
<pre>
dn: {$users_to_migrate.$key.dn}
{$users_to_migrate.$key.before}
</pre>
</div>
{t}After migration{/t}
<div style='padding-left:20px;'>
<pre>
dn: {$users_to_migrate.$key.dn}
{$users_to_migrate.$key.after}
</pre>
</div>
						</div>
					{/if}
				{else}
					<input type='checkbox' name='migrate_{$key}'>
					{$users_to_migrate.$key.dn}
				{/if}

				<br>
				

			{/foreach}
			<br>

			{if $user_details}
			<input type='submit' name='users_visible_migrate_refresh' value='{t}Hide changes{/t}'>
			{else}
			<input type='submit' name='users_visible_migrate_whatsdone' value='{t}Show changes{/t}'>
			{/if}

			<p class='seperator'>&nbsp;</p>	

			<div style='width:99%; text-align:right; padding-top:5px;'>
				<input type='submit' name='users_visible_migrate_migrate' value='{t}Apply{/t}'>
				&nbsp;
				<input type='submit' name='users_visible_migrate_close' value='{t}Cancel{/t}'>
			</div>
	{/if}
    </div>
</div>
