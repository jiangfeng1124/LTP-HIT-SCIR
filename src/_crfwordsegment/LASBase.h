#ifndef __LAS_BASE__
#define __LAS_BASE__

#define LAS_NS_BEG namespace las {
#define LAS_NS_END }; // end of namespace las

LAS_NS_BEG

const int MaxLookupAtomNum = 4; //the maximum atom number to look up
///����ĳ���������graph���
const int MaxGraphMatrixSize = 1024; ///�������СΪ100��100���������С�����ǽ��ᷢ�����·���
const int MaxWordArrayLength = 2048;      ///����Ԥ����Ĵʵ���󳤶ȣ������ó��ȵĽ��ᵼ���ڴ����·���
const int MaxWordPathMatrixSize = 2048;
const int MaxWordPathLinkLength = 64;
const int MaxLinkLength = 64;

LAS_NS_END

#endif
