#pragma once
//*******************************************************
// Purpose: Base class for all declarations
//
// Author: Philip Howard
// Email:  phil.howard@oit.edu
// Edited-By:   Alexander Tappin
// Date: 2/20/2015
//
//*******************************************************

#include <string>
#include <list>
using std::list;

#include "cAstNode.h"
#include "cAstList.h"
#include "cDeclNode.h"

using std::list;

class cDeclsNode : public cAstNode
{
  public:
    // constructor places first decl in list
    cDeclsNode(cDeclNode *decl) : cAstNode()
    {
        mList = new list<cDeclNode *>();
        mList->push_back(decl);
    }

    // add a declaration to the list
    void AddNode(cDeclNode *decl) 
    {
        mList->push_back(decl);
    }

    virtual std::string toString()
    {
        std::string result("DECLS:\n{\n");
        result += ListToString<cDeclNode *>(mList, true);
        result += "}\n";

        return result;
    }
    
    virtual int Computeoffsets(int base)
    {
        int offset = base;
        
        for(auto &it: *mList)
        {
          offset = it->Computeoffsets(offset);
        }
        
        mSize = offset - base;
        return offset;
    }

    virtual void GenerateCode()
    {
            list<cDeclNode*>::iterator it;
            
            for (it = mList->begin(); it != mList->end(); it++)
                (*it)->GenerateCode();
    }
    
    int Size()
    {
        return mSize;
    }
  protected:
    list<cDeclNode *> *mList;       // list of delcarations
    int mSize;
};

