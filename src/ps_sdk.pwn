/*

Version: MPL 1.1

The contents of this file are subject to the Mozilla Public License Version 
1.1 the "License"; you may not use this file except in compliance with 
the License. You may obtain a copy of the License at 
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
for the specific language governing rights and limitations under the
License.

Portions created by the Initial Developer are Copyright (c) 2022
the Initial Developer. All Rights Reserved.

*/


//////////////////////// == API == ////////////////////////

forward PS_CallRemoteFunction(funcname[],args__[]);
public PS_CallRemoteFunction(funcname[],args__[])
{
    dpp_print("PS_CallRemoteFunction called: funcname - '%s', args__ - '%s'",funcname,args__);
    new args[dpp_maxformargs][dpp_maxsymbolchar/2];
    dpp_parseline(args__,args,',');
    for(new i; i < dpp_maxformargs; i++)
    {
        dpp_codetrim(args[i]);
    }
    dpp_argclasscheck(funcname);
    dpp_argoclasscheck(funcname);
    for(new i; i < dpp_maxfuncs; i++)
    {
        if(!strcmp(dpp_funcname[i], funcname))
        {
            if(dpp_hookform[i] == 0)
            {
                for(new argid; argid < dpp_maxformargs; argid++)
                {
                    strmid(dpp_args[i][argid][dpp_argvalue],
                        args[argid],
                        0,
                        dpp_argcharsize/2,
                        dpp_argcharsize/2);
                }
                dpp_returned[i] = 0;
                dpp_processfunc = i;
                dpp_subexecute(dpp_funccodeblock[i], i);
                //dpp_debug("dpp_funccodeblock[i]:%s",dpp_funccodeblock[i]);

                if(dpp_option_hooking == 1)
                {
                    for(new hookfuncid; hookfuncid < dpp_maxfuncs; hookfuncid++)
                    {
                        if(!strcmp(dpp_funcname[hookfuncid], funcname))
                        {
                            if(dpp_hookform[hookfuncid] == 1)
                            {
                                for(new argid; argid < dpp_maxformargs; argid++)
                                {
                                    strmid(dpp_args[hookfuncid][argid][dpp_argvalue],
                                        args[argid],
                                        0,
                                        dpp_argcharsize/2,
                                        dpp_argcharsize/2);
                                }
                                dpp_processfunc = hookfuncid;
                                //dpp_warning("#1 Hookfunc: '%s' | Code: '%s'",dpp_funcname[hookfuncid],dpp_funccodeblock[hookfuncid]);
                                dpp_subexecute(dpp_funccodeblock[hookfuncid], hookfuncid);
                                //dpp_warning("#2 Hookfunc: '%s' | Code: '%s'",dpp_funcname[hookfuncid],dpp_funccodeblock[hookfuncid]);
                                //dpp_debug("dpp_funccodeblock[hookfuncid]:%s",dpp_funccodeblock[hookfuncid]);
                            }
                        }
                    }
                }
                dpp_clearformstack(dpp_processfunc); 
                dpp_deletestaticvars();
                dpp_processfunc = DPP_INVALID_FORM_ID;
                return 1;
            }
        }
    }
    return 0;
}