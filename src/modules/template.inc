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



stock dpp_createtemplate(name[], const func[])
{
    for(new i; i < dpp_maxtemplate; i++)
    {
        if(dpp_validtemplate[i] == 0)
        {
            if(dpp_workingclassid != dpp_invalidclass)
            {
                new newvalue[dpp_argcharsize];
                format(newvalue,sizeof(newvalue),"DPPCz@%s_%s",dpp_classname[dpp_workingclassid],name);
                strmid(name, newvalue, 0, dpp_argcharsize,dpp_argcharsize);
            }
            dpp_symbolcheck__(name);
            dpp_validtemplate[i] = 1;
            strmid(dpp_templatename[i], name, 0, dpp_maxstrsize,dpp_maxstrsize);
            strmid(dpp_templaterepl[i], func, 0, dpp_maxstrsize,dpp_maxstrsize);
            return 1;
        }
    }
    return 1;
}