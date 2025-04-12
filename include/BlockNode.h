/*
	This class is used to
	Copyright(c) 2024-present Ranyodh Singh Mandur.

*/

#pragma once

#include <vector>
#include <memory>

#include <string>

namespace Princess {

	//////////////////////////////////////////////
	// Base Block Node Struct
	//////////////////////////////////////////////

	struct BlockNode
	{
	public:
		std::string m_Name;
		std::string m_CodeSnippet;
		int m_LineNumber = -1;
		unsigned int m_InputLineNumber; //will start at lineNumber 0 originating from the "Program Enter" node, dictates order
		const unsigned int m_ID;
		int m_ParentID = -1; //initialize to -1 to indicate no parent , id's are strictly positive
		bool m_IsRootExecutable = false;

		std::vector<std::unique_ptr<BlockNode>> m_Children;

	public:
		BlockNode(const std::string& fp_Name, const std::string& fp_CodeSnippet, const unsigned int fp_ID)
			: m_Name(fp_Name), m_CodeSnippet(fp_CodeSnippet), m_ID(fp_ID) {}

		BlockNode(const std::string& fp_Name, const unsigned int fp_ID)
			: m_Name(fp_Name), m_ID(fp_ID) {}

		BlockNode(const unsigned int fp_ID)
			: m_ID(fp_ID) {}

		virtual ~BlockNode() = default;

	public:
		virtual std::string ToScript(unsigned int depth = 0) const{
			std::string indent(depth * 4, ' '); // 4 spaces per indent level
			return indent + m_CodeSnippet + "\n";
		}
	};

	struct VariableDefinitionBlockNode : public BlockNode
	{
		VariableDefinitionBlockNode(const std::string& fp_Name, const unsigned int fp_ID) : BlockNode(fp_ID)
		{
			m_Name = fp_Name;
		}

	public:
		std::string ToScript(unsigned int depth = 0) const override {
			std::string indent(depth * 4, ' '); // 4 spaces per indent level
			return indent + m_Name + " = " + m_CodeSnippet;
		}
	};

	//////////////////////////////////////////////
	// Function Nodes
	//////////////////////////////////////////////

	struct FunctionDefinitionBlockNode : public BlockNode
	{
	public:
		FunctionDefinitionBlockNode(const unsigned int fp_ID) : BlockNode(fp_ID)
		{

		}

	public:
		std::string ToScript(unsigned int depth = 0) const override {
			std::string indent(depth * 4, ' '); // 4 spaces per indent level
			return indent + "def " + m_Name + ":" + "\n";
		}
	};

	struct FunctionBlockNode : public BlockNode
	{
	public:
		FunctionBlockNode(const std::string& fp_Name, const unsigned int fp_ID) : BlockNode(fp_ID)
		{
			m_Name = fp_Name; //name actually matters here hehehe xd
		}

	public:
		std::string ToScript(unsigned int depth = 0) const override {
			std::string indent(depth * 4, ' '); // 4 spaces per indent level
			return indent + "def " + m_Name + ":" + "\n";
		}

	public:
		std::vector<std::string> m_ListOfArgs = {};
	};

	//////////////////////////////////////////////
	// Container Nodes
	//////////////////////////////////////////////

	struct DictionaryBlockNode : public BlockNode
	{
	public:
		DictionaryBlockNode(const std::string& fp_Name, const unsigned int fp_ID) : BlockNode(fp_ID)
		{
			m_Name = fp_Name;
		}

	public:
		std::string ToScript(unsigned int depth = 0) const override {
			std::string indent(depth * 4, ' '); // 4 spaces per indent level
			return indent + m_Name + " = " + m_CodeSnippet;
		}
	};

	struct ListBlockNode : public BlockNode
	{
		ListBlockNode(const std::string& fp_Name, const unsigned int fp_ID) : BlockNode(fp_ID)
		{
			m_Name = fp_Name;
		}

	public:
		std::string ToScript(unsigned int depth = 0) const override {
			std::string indent(depth * 4, ' '); // 4 spaces per indent level
			return indent + m_Name + " = " + m_CodeSnippet;
		}
	};

	//////////////////////////////////////////////
	// Loop Nodes
	//////////////////////////////////////////////

	struct WhileLoopBlockNode : public BlockNode
	{
	public:
		WhileLoopBlockNode(const std::string& fp_Name, const std::string& fp_CodeSnippet, const unsigned int fp_ID) : BlockNode(fp_ID)
		{
			m_Name = "while";
		}

	public:
		std::string ToScript(unsigned int depth = 0) const override {
			std::string indent(depth * 4, ' '); // 4 spaces per indent level
			return indent + "while " + m_CodeSnippet + ":" + "\n";
		}
	};

	struct ForLoopBlockNode : public BlockNode
	{
	public:
		ForLoopBlockNode(const unsigned int fp_ID) : BlockNode(fp_ID)
		{
			m_Name = "for";
		}

	public:
		std::string ToScript(unsigned int depth = 0) const override {
			std::string indent(depth * 4, ' '); // 4 spaces per indent level
			return indent + "for " + m_CodeSnippet + ":" + "\n";
		}
	};

	struct ForEachBlockNode : public BlockNode
	{
	public:
		ForEachBlockNode(const std::string& fp_CodeSnippet, const unsigned int fp_ID) : BlockNode(fp_ID)
		{
			m_Name = "for";
		}

	public:
		std::string ToScript(unsigned int depth = 0) const override {
			std::string indent(depth * 4, ' '); // 4 spaces per indent level
			return indent + "foreach " + m_CodeSnippet + ":" + "\n";
		}
	};

	struct BreakBlockNode : public BlockNode
	{
	public:
		BreakBlockNode(const unsigned int fp_ID) : BlockNode(fp_ID)
		{
			m_Name = "break";
			m_CodeSnippet = "break";
		}

		std::string ToScript(unsigned int depth = 0) const override {
			std::string indent(depth * 4, ' '); // 4 spaces per indent level
			return indent + "break" + "\n";
		}
	};

	//////////////////////////////////////////////
	// Conditional Flow Nodes
	//////////////////////////////////////////////

	struct IfBlockNode : public BlockNode
	{
	public:
		IfBlockNode(const std::string& fp_CodeSnippet, const unsigned int fp_ID) : BlockNode(fp_ID)
		{
			m_Name = "if";
		}

	public:
		std::string ToScript(unsigned int depth = 0) const override {
			std::string indent(depth * 4, ' '); // 4 spaces per indent level
			return indent + "if " + m_CodeSnippet + ":" + "\n";
		}
	};

	struct ElseIfBlockNode : public BlockNode
	{
	public:
		ElseIfBlockNode(const std::string& fp_CodeSnippet, const unsigned int fp_ID)
			: BlockNode(fp_ID)
		{
			m_Name = "elif";
		}

	public:
		std::string ToScript(unsigned int depth = 0) const override {
			std::string indent(depth * 4, ' '); // 4 spaces per indent level
			return indent + "elif " + m_CodeSnippet + ":" + "\n";
		}

	};

	struct ElseBlockNode : public BlockNode
	{
	public:
		ElseBlockNode(const std::string& fp_CodeSnippet, const unsigned int fp_ID) : BlockNode(fp_ID)
		{
			m_Name = "else";
		}

		std::string ToScript(unsigned int depth = 0) const override {
			std::string indent(depth * 4, ' '); // 4 spaces per indent level
			return indent + "else: " + "\n";
		}
	};
}


