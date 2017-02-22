// Node.cpp : implementation file
//

#include "stdafx.h"
#include "ModalDialogNodes.h"
#include "Node.h"
#include "afxdialogex.h"


// CNode dialog

IMPLEMENT_DYNAMIC(CNode, CDialogEx)

CNode::CNode(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNode::IDD, pParent)
	, m_id(0)
	, m_x(0)
	, m_y(0)
{

}

CNode::~CNode()
{
}

void CNode::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ID, m_id);
	DDX_Text(pDX, IDC_X, m_x);
	DDX_Text(pDX, IDC_Y, m_y);
}


BEGIN_MESSAGE_MAP(CNode, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNode::OnBnClickedOk)
END_MESSAGE_MAP()


// CNode message handlers


void CNode::OnBnClickedOk()
{
	UpdateData(1); // actualiza variables
	CDialogEx::OnOK();
}
