#include "qt/element/QtCodeSnippet.h"

#include <QHBoxLayout>
#include <QPushButton>

#include "qt/element/QtCodeFile.h"

QtCodeSnippet::QtCodeSnippet(
	uint startLineNumber,
	const std::string& title,
	const std::string& code,
	std::shared_ptr<TokenLocationFile> locationFile,
	QtCodeFile* file
)
	: QWidget(file)
	, m_codeArea(std::make_shared<QtCodeArea>(startLineNumber, code, locationFile, file, this))
{
	setObjectName("code_snippet");

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);
	layout->setAlignment(Qt::AlignTop);
	setLayout(layout);

	m_title = new QPushButton(title.c_str(), this);
	m_title->setObjectName("title_label");
	m_title->minimumSizeHint(); // force font loading
	m_title->setAttribute(Qt::WA_LayoutUsesWidgetRect); // fixes layouting on Mac
	m_title->setSizePolicy(sizePolicy().horizontalPolicy(), QSizePolicy::Fixed);
	layout->addWidget(m_title);

	layout->addWidget(m_codeArea.get());
}

QtCodeSnippet::~QtCodeSnippet()
{
}

void QtCodeSnippet::addMaximizeButton()
{
	m_codeArea->addMaximizeButton();
}

int QtCodeSnippet::lineNumberDigits() const
{
	return m_codeArea->lineNumberDigits();
}

void QtCodeSnippet::updateLineNumberAreaWidthForDigits(int digits)
{
	m_codeArea->updateLineNumberAreaWidthForDigits(digits);
}

void QtCodeSnippet::updateContent()
{
	m_codeArea->updateContent();
}
