#include "stdafx.h"
#include "Stack.h"
#include "Additional Source Files\grammartoparsetable\ParsingTable.h"
#include <stdlib.h>
#include "Additional Source Files\ParseTreeStruct\ParseTree.h"

//See documentation for explanation on the input parameters
struct ParseTree* Parse(int ** __Grammers, int *__Rows, int __countRows,  int __countTerminals,int __countNonterminals, int *__intInput, int __CountInput){

	int **_parseTable;
	struct stack *_ItemStack = (struct stack*)malloc(sizeof(struct stack));
	int i;
	int *_production;
	struct ParseTree *_ptrHeader;
	int *_adjInput = (int *)malloc(sizeof(int)*(__CountInput+1));
	struct ParseTree *_ptrCurrentNode;
	
	//M[X, a]
	int M_a;
	//the number of items in the production[] array
	int _countProductionOutput;
	_parseTable = Generate(__Grammers, __Rows, __countRows, __countTerminals, __countNonterminals);
	//push $
	Push(&_ItemStack, __countTerminals +__countNonterminals+1);
	_ptrCurrentNode = CreateParseTree();
	_ptrCurrentNode->value =0;
	_ptrHeader = _ptrCurrentNode;
	
	//push First production
	Push(&_ItemStack, 0);
	i =0;
	
	//add the endmarker to the input;
	for (int i = 0; i <__CountInput;i++){
		_adjInput[i] =__intInput[i];
	}
	//$
	_adjInput[__CountInput] = __countNonterminals + __countNonterminals+1;
	
	while (_ItemStack->value != __countTerminals +__countNonterminals+1){
		//if terminals match
		if (_ItemStack->value == _adjInput[i]) {
			_ptrCurrentNode =  GetNextInStack(_ptrCurrentNode);
			Pop(&_ItemStack);
		
			i++;
		}
		//Epsilon character
		else if(_ItemStack->value ==__countNonterminals+__countNonterminals){
			_ptrCurrentNode =  GetNextInStack(_ptrCurrentNode);
			Pop(&_ItemStack);
		}
		else if(_ItemStack->value >=__countNonterminals){
			printf("Error, Terminals don't match\n");
			abort();
		}
		else if(_parseTable[_ItemStack->value][_adjInput[i]-__countNonterminals]==-1){
			printf("Error, Error entry in parse table\n");
			abort();
		}
		else{
			if (_adjInput[i] == __countNonterminals + __countTerminals +1){
				//$ sign
				M_a = _parseTable[_ItemStack->value][_adjInput[i]-__countNonterminals-1];	
			}
			else{
				M_a = _parseTable[_ItemStack->value][_adjInput[i]-__countNonterminals];	
			}
			Pop(&_ItemStack);
			//get items in production
			_production = GetProduction(__Grammers, M_a, __countTerminals+ __countNonterminals+1, &_countProductionOutput);
			//add items to tree
			 Add(_ptrCurrentNode, _production, _countProductionOutput);
			 _ptrCurrentNode = _ptrCurrentNode->FirstChild;
			 for (int j =  _countProductionOutput-1; j >=0; j--){
				 if (_production[j] !=-1){
					Push(&_ItemStack,  _production[j]);
				 }
			 }
		}
	}

	return _ptrHeader;
}

