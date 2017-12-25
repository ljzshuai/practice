#ifndef LEXCEL_H
#define LEXCEL_H
#include <qstring.h>
#include <qaxobject.h>
#include <stdint.h>
namespace LJZ{
	using UInt = uint32_t;

	class LExcel;
	class LCell
	{
	public:
		LCell() :_row(1), _column(1){}
		explicit LCell(UInt row = 1, UInt column = 1) :_row(row),_column(column){}
		void setValue(UInt row, UInt column){ _row = row; _column = column; }
	private:
		UInt _row; 
		UInt _column;
		friend LExcel;
	};

	class LExcel
	{
	public:
		LExcel();
		bool save();
		bool saveAs(const QString&);
		void DisplayAlerts(bool show);

		QVariant getValue(LCell);
		QVariant getValue(UInt, UInt);
		bool setValue(LCell, const QVariant& value);
		bool setValue(UInt row, UInt column, const QVariant& value);
		bool setValue(LCell start,LCell end, const QVariant& value);	
		bool setValue(UInt cell1_row, UInt Cell1_column, UInt cell2_row, UInt cell2_column, const QVariant&value);
	
		UInt SheetCount();
		bool addSheet(QString name);
		bool deleteSheet(UInt item);
		bool changeWorkSheet(UInt item);
		bool setSheetName(UInt item,QString name);
		QString getSheetName(UInt item);

		UInt getStartRowNum(UInt sheet_item);
		UInt getStartColumn(UInt sheet_item);
		UInt getRowCount(UInt sheet_item);
		UInt getColumnCount(UInt sheet_item);

		bool open(QString path = QString());
		bool close();
		~LExcel();
	private:
		enum {
			LExcelNewExcel = 1,
			LExcelOpen = 2,
		};
		LExcel(const QString&filePath);
		LExcel(const LExcel&) = delete;
		LExcel operator=(const LExcel&) = delete;
		QString numColumnToString(UInt);
		QAxObject* getSheet(UInt item);

		QAxObject* _excel;
		QAxObject* _work_books;
		QAxObject* _work_book;
		QAxObject* _work_sheets;
		QAxObject* _work_sheet;

		UInt _status;
	};
}
#endif // LEXCEL_H
