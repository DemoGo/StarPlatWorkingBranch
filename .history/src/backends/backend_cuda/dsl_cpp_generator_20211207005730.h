#ifndef DSL_CPP_GENERATOR
#define DSL_CPP_GENERATOR

#include <cstdio>
#include "../dslCodePad.h"
#include "../../ast/ASTNodeTypes.hpp"
#include "../../parser/includeHeader.hpp"
//#include "dslCodePad.h"


class dsl_cpp_generator
{
  private:

  dslCodePad header;
  dslCodePad main;
  FILE *headerFile;
  FILE *bodyFile;
  char* fileName;

  public:
  dsl_cpp_generator()
  {
    headerFile=NULL;
    bodyFile=NULL;
    fileName=new char[1024];

  }

  void setFileName(char* f);
  bool generate();
  void generation_begin();
  void generation_end();
  bool openFileforOutput();
  void closeOutputFile();
  const char* convertToCppType(Type* type);
  const char* getOperatorString(int operatorId);
  void generateFunc(ASTNode* proc);
  void generateFuncHeader(Function* proc,bool isMainFile);
  void generateProcCall(proc_callStmt* procCall);
  void generateVariableDecl(declaration* decl);
  void generateStatement(statement* stmt);
  void generateAssignmentStmt(assignment* assignStmt);
  void generateWhileStmt(whileStmt* whilestmt);
  void generateForAll(forallStmt* forAll);
  void generateFixedPoint(fixedPointStmt* fixedPoint);
  void generateIfStmt(ifStmt* ifstmt);
  void generateDoWhileStmt(dowhileStmt* doWhile);
  void generateBFS();
  void generateBlock(blockStatement* blockStmt, bool includeBrace=true);
  void generateReductionStmt(reductionCallStmt* reductnStmt);
  void generateBFSAbstraction(iterateBFS* bfsAbstraction);
  void generateExpr(Expression* expr);
  void generate_exprRelational(Expression* expr);
  void generate_exprInfinity(Expression* expr);
  void generate_exprLiteral(Expression* expr);
  void generate_exprIdentifier(Identifier* id);
  void generate_exprPropId(PropAccess* propId) ;
  void generate_exprProcCall(Expression* expr);
  void generate_exprArL(Expression* expr);
  void generateForAll_header();
  void generateForAllSignature(forallStmt* forAll);
  //void includeIfToBlock(forallStmt* forAll);
  bool neighbourIteration(char* methodId);
  bool allGraphIteration(char* methodId);
  blockStatement* includeIfToBlock(forallStmt* forAll);

  void generateId();
  void generateOid();
  void addIncludeToFile(char* includeName,dslCodePad& file,bool isCPPLib);
  void generatePropertyDefination(Type* type,char* Id);
  void findTargetGraph(vector<Identifier*> graphTypes,Type* type);
  void getDefaultValueforTypes(int type);

  void generateInitialization();
  void generateStatement1(statement* stmt);
  void generateFuncSSSPBody();
  void generateFuncCUDASizeAllocation();
  void generateFuncCudaMalloc();
  void generateBlockForSSSPBody(blockStatement* blockStmt,bool includeBrace);
  void generateStatementForSSSPBody(statement* stmt);
  void generateCudaMemCpyForSSSPBody();
  void generateFuncPrintingSSSPOutput();
  void generateFuncVariableINITForSSSP();
  void generateFuncTerminatingConditionForSSSP();
  //newly added for cuda speific handlings index
  void generateCudaIndex();
  void generateAtomicBlock();
  void generateVariableDeclForEdge(declaration* declStmt);
  void generateLocalInitForID();
  //new
  void castIfRequired(Type* type,Identifier* methodID,dslCodePad& main);
  void generateReductionCallStmt(reductionCallStmt* stmt);
  void generateReductionOpStmt(reductionCallStmt* stmt);
  void generate_exprUnary(Expression* expr);
  void generateForAll_header(forallStmt* forAll);
  void generatefixedpt_filter(Expression* filterExpr);

  bool elementsIteration(char* extractId);
  void generateCudaMallocStr(const char* dVar,const char* typeStr, const char* sizeOfType, bool isMainFile);
  void generateCudaMalloc(Type* type, const char* identifier, bool isMainFile);
  void generateCudaMemcpy(const char* dVar,const char* cVar,const char* typeStr, const char* sizeOfType, bool isMainFile,const char* from);

  //for algorithm specific function implementation headers

  void generateKernelFuncForTC();
  void generateKernelFuncForPR();
  void generateKernelFuncForSSSP(ASTNode* proc);
  void generateKernelFuncForBC();

  

  

};

 static const char* INTALLOCATION = "new int";
 static const char* BOOLALLOCATION = "new bool";
 static const char* FLOATALLOCATION = "new float";
 static const char* DOUBLEALLOCATION = "new double";
#endif