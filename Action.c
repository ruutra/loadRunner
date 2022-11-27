#include <..\Parametrs\functions.c>
Action()
{	
	lr_start_transaction("UC01_TC1_mainPage_Open");
	
	mainPage_Open();
	
	lr_end_transaction("UC01_TC1_mainPage_Open", LR_AUTO);
	
	csrfmiddlewaretoken();

	lr_start_transaction("UC01_TC2_loginPage");
	
	loginPage_Open();
	
	lr_end_transaction("UC01_TC2_loginPage", LR_AUTO);
	
	path();
	
	web_reg_find("Text=logout",
        "SaveCount=logout_Count",
        LAST );
	
	lr_start_transaction("UC01_TC3_LoginAdmin");
	
	web_submit_data("login", 
		"Action={protocol}://{host}:{port}/login/", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/login/?next=/", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={admin_login}", ENDITEM, 
		"Name=password", "Value={admin_password}", ENDITEM, 
		"Name=next", "Value=/", ENDITEM, 
		"Name=csrfmiddlewaretoken", "Value={csrfmiddlewaretoken}", ENDITEM, 
		LAST);

	lr_end_transaction("UC01_TC3_LoginAdmin",LR_AUTO);
	
		
	if (atoi(lr_eval_string("{logout_Count}")) > 0) {
        lr_output_message("Log on successful!");
    } else {
        lr_error_message("Log on failed!");
    }
	
	lr_start_transaction("UC01_TC4_ticketsPage");

	TicketList();
	
	lr_end_transaction("UC01_TC4_ticketsPage", LR_AUTO);


	lr_start_transaction("UC01_TC5_Logout");

	Logout();
	
	lr_end_transaction("UC01_TC5_Logout",LR_AUTO);

	return 0;
}