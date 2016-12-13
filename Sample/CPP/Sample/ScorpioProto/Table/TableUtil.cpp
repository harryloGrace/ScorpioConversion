#include "TableUtil.h"
#include <string.h>
#include <exception>
using namespace std;
namespace Scorpio {
	namespace Table {
		ITableUtil * TableUtil::IUtil = nullptr;
		float TableUtil::INVALID_FLOAT = -1.0f;
		double TableUtil::INVALID_DOUBLE = -1.0;

		char * TableUtil::GetBuffer(const char * fileName) {
			return IUtil != nullptr ? IUtil->GetBuffer(fileName) : nullptr;
		}
		void TableUtil::Warning(const char * message) {
			if (IUtil != nullptr)
				IUtil->Warning(message);
		}
		int TableUtil::ReadHead(ScorpioReader * reader, const char * fileName, const char * md5) {
			int iRow = reader->ReadInt32(); //����
			if (strcmp(reader->ReadString(), md5)) //��֤�ļ�MD5(���ṹ�Ƿ�ı�)
				throw std::exception("�ļ��汾��֤ʧ��");
			int i, j, number; 
			{
				number = reader->ReadInt32(); //�ֶ�����
				for (i = 0; i < number; ++i) {
					if (reader->ReadInt8() == 0) { //��������
						reader->ReadInt8(); //������������
						reader->ReadBool(); //�Ƿ�������
					}
					else { //�Զ�����
						reader->ReadString(); //�Զ���������
						reader->ReadBool(); //�Ƿ�������
					}
				}
			}
			int customNumber = reader->ReadInt32(); //�Զ���������
			for (i = 0; i < customNumber; ++i) {
				reader->ReadString(); //��ȡ�Զ���������
				number = reader->ReadInt32(); //�ֶ�����
				for (j = 0; j < number; ++j) {
					if (reader->ReadInt8() == 0) { //��������
						reader->ReadInt8(); //������������
						reader->ReadBool(); //�Ƿ�������
					}
					else { //�Զ�����
						reader->ReadString(); //�Զ���������
						reader->ReadBool(); //�Ƿ�������
					}
				}
			}
			return iRow;
		}
		bool TableUtil::IsInvalid(__int8 val) {
			return val == INVALID_INT8;
		}
		bool TableUtil::IsInvalid(__int16 val) {
			return val == INVALID_INT16;
		}
		bool TableUtil::IsInvalid(__int32 val) {
			return (val == INVALID_INT32);
		}
		bool TableUtil::IsInvalid(__int64 val) {
			return (val == INVALID_INT64);
		}
		bool TableUtil::IsInvalid(float val) {
			return (abs(INVALID_FLOAT - val) < 0.001f);
		}
		bool TableUtil::IsInvalid(double val) {
			return (abs(INVALID_DOUBLE - val) < 0.001f);
		}
		bool TableUtil::IsInvalid(const char * val) {
			return strlen(val) == 0;
		}
		bool TableUtil::IsInvalid(IData * val) {
			return val->IsInvalid();
		}
		bool TableUtil::IsInvalidInt8(__int8 val) {
			return val == INVALID_INT8;
		}
		bool TableUtil::IsInvalidInt16(__int16 val) {
			return val == INVALID_INT16;
		}
		bool TableUtil::IsInvalidInt32(__int32 val) {
			return (val == INVALID_INT32);
		}
		bool TableUtil::IsInvalidInt64(__int64 val) {
			return (val == INVALID_INT64);
		}
		bool TableUtil::IsInvalidFloat(float val) {
			return (abs(INVALID_FLOAT - val) < 0.001f);
		}
		bool TableUtil::IsInvalidDouble(double val) {
			return (abs(INVALID_DOUBLE - val) < 0.001f);
		}
		bool TableUtil::IsInvalidString(const char * val) {
			return strlen(val) == 0;
		}
		template<typename T>
		bool TableUtil::IsInvalidList(std::vector<T> val) {
			return val.empty();
		}
		bool TableUtil::IsInvalidData(IData * val) {
			return val->IsInvalid();
		}
	}
}