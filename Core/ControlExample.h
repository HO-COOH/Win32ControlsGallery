#pragma once
#include <string>
#include <memory>

class ControlBase;

class Content
{
public:
	void add(std::unique_ptr<ControlBase>&& control);
};

class ControlExample
{
public:
	void setHeaderText(std::string&& text);
	void setContent(Content&& content);
	void setOutput();
};

