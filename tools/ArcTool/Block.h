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
	CString m_strOrigSent;	//��������ʵ���ǵ�ԭʼ���ӣ���һ��
	CString m_strSentence;	//��λ�ñ�ŵľ��ӣ��ڶ���
	CString m_strPairs;		//�����ϵ��ϵ�ԣ�������
//����/n ����/v [������ʡ/ns �ض���/ns ������/ns �깴�/ns]ns ��/wp 
//[1]����/n [2]����/v [3]������ʡ/ns [4]�ض���/ns [5]������/ns [6]�깴�/ns [7]��/wp [8]<EOS>/<EOS> 
//[8]<EOS>_[2]����		[2]����_[1]����		[2]����_[6]�깴�		[6]�깴�_[5]������		[5]������_[4]�ض���		[4]�ض���_[3]������ʡ		
};

#endif // !defined(AFX_BLOCK_H__FACCD39A_3D7A_412C_99A0_3BD68599EA8E__INCLUDED_)
