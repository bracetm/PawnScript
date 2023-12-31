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

stock dpp_createiter(const name[], size)
{
    //dpp_symbolcheck__(name);
    for(new i; i < dpp_maxiter; i++)
    {
        if(dpp_validiter[i] == 0)
        {
            dpp_validiter[i] = 1;
            strmid(dpp_itername[i], name, 0, dpp_maxsymbolchar, dpp_maxsymbolchar);
            if(dpp_workingclassid != dpp_invalidclass)
            {
                new newvalue[dpp_argcharsize];
                format(newvalue,sizeof(newvalue),"DPPCi@%s_%s",dpp_classname[dpp_workingclassid],name);
                strmid(dpp_itername[i], newvalue, 0, dpp_argcharsize,dpp_argcharsize);
            }
            dpp_symbolcheck__(name);
            dpp_itersize[i] = size;
            for(new itervalid; itervalid < size; itervalid++)
            {
                dpp_itervalues[i][itervalid] = dpp_invaliditerval;
            }
            //dpp_error("Created an iter '%s'",name);
            return 1;
        }
    }
    return 1;
}

stock dpp_addvalue(const name[], value)
{
    new iterid = -1;
    for(new i; i < dpp_maxiter; i++)
    {
        if(dpp_strcmp(name, dpp_itername[i]))
        {
            if(dpp_validiter[i] == 1)
            {
                iterid = i;
                break;   
            }
        }
    }
    if(iterid == -1)
    {
        dpp_error("Iterator '%s' could not be found.",name);
        return 1;
    }
    for(new i; i < dpp_itersize[iterid]; i++)
    {
        if(dpp_itervalues[iterid][i] == dpp_invaliditerval)
        {
            dpp_itervalues[iterid][i] = value;
            break;   
        }
    }
    //dpp_error("Added a value '%i' to an iter '%s'",value,name);
    return 1;
}

stock dpp_removevalue(const name[], value)
{
    new iterid = -1;
    for(new i; i < dpp_maxiter; i++)
    {
        if(dpp_strcmp(name, dpp_itername[i]))
        {
            if(dpp_validiter[i] == 1)
            {
                iterid = i;
                break;   
            }
        }
    }
    if(iterid == -1)
    {
        dpp_error("Iterator '%s' could not be found.",name);
        return 1;
    }
    for(new i; i < dpp_itersize[iterid]; i++)
    {
        if(dpp_itervalues[iterid][i] == value)
        {
            dpp_itervalues[iterid][i] = dpp_invaliditerval;
            break;   
        }
    }
    //dpp_error("Removed a value '%i' from an iter '%s'",value,name);
    return 1;
}


stock dpp_deleteiter(const name[])
{
    for(new i; i < dpp_maxiter; i++)
    {
        if(dpp_strcmp(name, dpp_itername[i]))
        {
            if(dpp_validiter[i] == 1)
            {
                dpp_validiter[i] = 0;
                return 1;   
            }
        }
    }
    //dpp_error("Iterator '%s' could not be found.",name);
    return 0;
}