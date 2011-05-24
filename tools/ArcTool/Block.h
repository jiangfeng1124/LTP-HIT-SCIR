// Block.h: interface for the CBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLOCK_H__FACCD39A_3D7A_412C_99A0_3BD68599EA8E__INCLUDED_)
#define AFX_BLOCK_H__FACCD39A_3D7A_412C_99A0_3BD68599EA8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBlock  
{
public:
	CBlock();
	virtual ~CBlock();
	CString m_strOrigSent;	//带有命名实体标记的原始句子，第一行
	CString m_strSentence;	//带位置标号的句子，第二行
	CString m_strPairs;		//依存关系关系对，第三行
//记者/n 来到/v [黑龙江省/ns 肇东市/ns 东发乡/ns 旮旯村/ns]ns 。/wp 
//[1]记者/n [2]来到/v [3]黑龙江省/ns [4]肇东市/ns [5]东发乡/ns [6]旮旯村/ns [7]。/wp [8]<EOS>/<EOS> 
//[8]<EOS>_[2]来到		[2]来到_[1]记者		[2]来到_[6]旮旯村		[6]旮旯村_[5]东发乡		[5]东发乡_[4]肇东市		[4]肇东市_[3]黑龙江省		
};

#endif // !defined(AFX_BLOCK_H__FACCD39A_3D7A_412C_99A0_3BD68599EA8E__INCLUDED_)
