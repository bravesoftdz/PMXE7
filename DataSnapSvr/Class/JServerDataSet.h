//---------------------------------------------------------------------------

#ifndef JServerDataSetH
#define JServerDataSetH
#include <ADODB.hpp>
#include <DB.hpp>
#include "BaseServerClass.h"
//---------------------------------------------------------------------------
class TJServerDataSet : public TDMBaseServerClass
{
private:
	TADODataSet *m_MasterDataSet;
	TADODataSet *m_DetailDataSet;
	TADOStoredProc *m_StoredProc;

	TADOQuery *m_BuildQuery;

	TADOConnection *m_Connection;
	TADOConnection *m_BuildConn;
	TADOQuery *m_Query;
	TADOQuery *b_Query;
	TADOQuery *LogQuery;
	String m_ClassCode;

	bool m_Active;
	int m_Status;
	int m_DataSetType;

	String m_MasterSQLString;
	String m_DetailSQLString;
	String m_MasterFixedWhereString;
	String m_MasterWhereString;
	String m_DetailFixedWhereString;
	String m_DetailWhereString;
	String m_MasterFixedOrderString;
	String m_MasterOrderString;
	String m_DetailFixedOrderString;
	String m_DetailOrderString;
	String m_MasterFixedGroupString;
	String m_MasterGroupString;
	String m_DetailFixedGroupString;
	String m_DetailGroupString;
	String m_MasterDisplayName;
	String m_DetailDisplayName;
	String m_MasterDisplayField;
	String m_DetailDisplayField;
	TStringList *m_MasterLinkFields;
	TStringList *m_DetailLinkFields;
	String m_MasterFilterFields;
	String m_DetailFilterFields;
	String m_MasterFieldAttr;
	String m_DetailFieldAttr;
	String m_MasterFieldExpr;
	String m_DetailFieldExpr;
	String m_MasterAttrType;
	String m_DetailAttrType;

	String m_MasterKeyFields;
	String m_DetailKeyFields;

	String m_ClientDataSetHandle;
	TStringList *m_ServerBuffer;

	int FSysDbType;
	int FAccDbType;
	String FUserCode;
	String FUserIP;
	String FAcckBook;
	TJSONObject*  SendErrorMessage(int errortype, int errorcode, String errormessage);
	TJSONObject*  SendFailMessage(int operate, String errormessage);
	void  WriteUserLog(int type, String Desc);
	void  InitServerDataSet(String ClassCode);
protected:
	String  BuildLinkStr();
	String  BuildLinkFields();
	void  ExtractLinkFields(String value);
	void  BuildDetailFilter();
	int  CheckFieldType(TField *Field);
public:
	__fastcall TJServerDataSet(TComponent* Owner);
	__fastcall ~TJServerDataSet();

	/*********************************************************************
	// ����JSONObject��ʽ������(Data)������Ϣ(Cols)��ҵ������Ϣ��ɣ�
	//{Master:{Data:[],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
	// Detail:{Data:[],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
	// Operate:,Status:,DataSetType:,MasterKeyFields:,MasterDisplayName:,
	// MasterDisplayField:,MasterFilterFields:,MasterFieldAttr:,MasterAttrType:,MasterFieldExpr:,
	// MasterSqlString:,MasterFixedWhere:,MasterFixedOrder:,MasterFixedGroup:,
	// DetailKeyFields:,DetailDisplayName:,DetailDisplayField:,DetailFilterFields:,
	// DetailFieldAttr:,DetailAttrType:,DetailFieldExpr:,DetailSqlString:,
	// DetailFixedWhere:,DetailFixedOrder:,DetailFixedGroup,MasterLinkFields:,DetailLinkFields:}
	**********************************************************************/
	TJSONObject*  GetInitResult(String ClassCode);
	/*********************************************************************
	// ����JSONObject��ʽ
	// {MasterWhere:,MasterOrder:,DetailWhere:,DetailOrder:}
	// ����JSONObject��ʽ������(Data)������Ϣ(Cols)��ɣ�
	//{Master:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
	// Detail:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
	// Status:}
	**********************************************************************/
	TJSONObject*  Open(TJSONObject *Json, String ClassCode);
	/*********************************************************************
	// ����JSONObject��ʽ
	//{Master:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
	// Detail:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
	//{OldMaster:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
	// OldDetail:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
	// MasterStatus:1-���;2-�޸�;3-����, DetailStatus:1-���;3-����;2-�޸�;0-ɾ��}
	// ����JSONObject��ʽ������(Data)������Ϣ(Cols)��ҵ������Ϣ��ɣ�
	//{Master:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
	// Detail:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
	// Status:}
	**********************************************************************/
	TJSONObject*  Update(TJSONObject *Json, String ClassCode);
	/*********************************************************************
	// ����JSONObject��ʽ
	//{Master:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]}
	// ����JSONObject��ʽ��ҵ������Ϣ��ɣ�
	// {Status:}
	**********************************************************************/
	TJSONObject*  Delete(TJSONObject *Json, String ClassCode);
	/*********************************************************************
	// ����JSONObject��ʽ
	// Detail:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]}
	// ����JSONObject��ʽ��ҵ������Ϣ��ɣ�
	// {Status:}
	**********************************************************************/
	TJSONObject*  DeleteDetail(TJSONObject *Json, String ClassCode);
	/*********************************************************************
	// ����JSONObject��ʽ
	// ����JSONObject��ʽ��ҵ������Ϣ��ɣ�
	// {Status:}
	**********************************************************************/
	TJSONObject*  ValidateData(TJSONObject *Json, String ClassCode);
	/*********************************************************************
	// ����JSONObject��ʽ
	// ����JSONObject��ʽ��ҵ������Ϣ��ɣ�
	// {Status:}
	**********************************************************************/
	TJSONObject*  CmdExec(TJSONObject *Json, String ClassCode);
	/*********************************************************************
	// ����JSONObject��ʽ
	//{Master:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]}
	// ����JSONObject��ʽ��ҵ������Ϣ��ɣ�
	//{Master:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
	// Status:}
	**********************************************************************/
	TJSONObject*  Check(TJSONObject *Json, String ClassCode);
	/*********************************************************************
	// ����JSONObject��ʽ
	//{Master:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]}
	// ����JSONObject��ʽ��ҵ������Ϣ��ɣ�
	//{Master:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
	// Status:}
	**********************************************************************/
	TJSONObject*  CloseOff(TJSONObject *Json, String ClassCode);
	/*********************************************************************
	// ����JSONObject��ʽ
	//{Master:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]}
	// ����JSONObject��ʽ��ҵ������Ϣ��ɣ�
	//{Master:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
	// Status:}
	**********************************************************************/
	TJSONObject*  Revoke(TJSONObject *Json, String ClassCode);
	/*********************************************************************
	// ����JSONObject��ʽ
	//{Master:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]}
	// ����JSONObject��ʽ��ҵ������Ϣ��ɣ�
	//{Master:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
	// Status:}
	**********************************************************************/
	TJSONObject*  Tally(TJSONObject *Json, String ClassCode);
	/*********************************************************************
	// ����JSONObject��ʽ
	// {SQLStr:}
	// ����JSONObject��ʽ
	// {Status:}
	**********************************************************************/
	TJSONObject*  ExecSQL(TJSONObject *Json);
	/*********************************************************************
	// ����JSONObject��ʽ
	//{Master:{Data:[{FieldName0:FieldValue0},{FieldName1:FieldValue1},{FieldName2:FieldValue2}...],
	//         Cols:[{FieldIndex:},{FieldType:},{FieldSize:},{FieldName:},{Required:}...]},
	// Status:}
	**********************************************************************/
	TJSONObject*  QueryOpen(String SQLText);
	/*********************************************************************
	// ����JSONObject��ʽ
	// {Status:,RowsAffected:}
	**********************************************************************/
	TJSONObject*  QueryExecSQL(String SQLText);

	// ִ��ϵͳ��
	TJSONObject*  QuerySysOpen(String SQLText);
	TJSONObject*  QuerySysExecSQL(String SQLText);
};
#endif