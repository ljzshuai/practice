#include "lexcel.h"
#include <qregexp.h>
#include <math.h>
#include <vector>
namespace LJZ{

	LExcel::LExcel()
		:_status(0)
	{
		_excel = new QAxObject("Excel.Application");
		_excel->dynamicCall("SetVisible (bool Visible)", "false");
		_excel->setProperty("DisplayAlerts", false);
		_work_books = _excel->querySubObject("WorkBooks");
	}

	void LExcel::DisplayAlerts(bool show)
	{
		_excel->setProperty("DisplayAlerts", show);
	}

	UInt LExcel::SheetCount()
	{
		if (!(_status & LExcelOpen))
			return false;

		return _work_sheets->property("Count").toUInt();
	}

	bool LExcel::setSheetName(UInt item, QString name)
	{
		if (!(_status & LExcelOpen))
			return false;

		if (!(_status & LExcelOpen))
			return false;
		if (item == 0 || item > SheetCount())
			return false;

		QAxObject *sheet = _work_sheets->querySubObject("Item(int)", item);
		return sheet->setProperty("Name", name);
	}

	QString LExcel::getSheetName(UInt item)
	{
		if (!(_status & LExcelOpen))
			return false;

		if (!(_status & LExcelOpen))
			return false;
		if (item == 0 || item > SheetCount())
			return false;

		QAxObject* sheet = _work_sheets->querySubObject("Item(int)", item);
		return sheet->property("Name").toString();
	}

	bool LExcel::changeWorkSheet(UInt item)
	{
		if (!(_status & LExcelOpen))
			return false;
		if (item == 0 || item > SheetCount())
			return false;

		_work_sheet = _work_sheets->querySubObject("Item(int)", item);
		if (!_work_sheet)
		{
			close();
			return false;
		}
		return true;
	}

	bool LExcel::deleteSheet(UInt item)
	{
		if (!(_status & LExcelOpen))
			return false;
		if (item == 0 || item > SheetCount())
			return false;

		QAxObject *del_sheet = _work_sheets->querySubObject("Item(int)", num);
		return del_sheet->dynamicCall("delete").toInt();
	}

	bool LExcel::addSheet(QString name)
	{
		if (!(_status & LExcelOpen))
			return false;

		QAxObject *last_sheet = _work_sheets->querySubObject("Item(int)", SheetCount());
		QAxObject *new_sheet = _work_sheets->querySubObject("Add(QVariant)", last_sheet->asVariant());
		last_sheet->dynamicCall("Move(QVariant)", new_sheet->asVariant());
		new_sheet->setProperty("Name", name);
		return true;
	}

	QAxObject*  LExcel::getSheet(UInt item)
	{
		if (!(_status & LExcelOpen))
			return nullptr;
		if (item == 0 || item > SheetCount())
			return nullptr;

		return _work_sheets->querySubObject("Item(int)", item);
	}

	bool LExcel::open(QString path)
	{
		if (path.isEmpty())
		{
			_status |= LExcelNewExcel;
			_work_books->dynamicCall("ADD");
		}
		else
			_work_books->dynamicCall("Open(const QString&)", path);

		_work_book = _excel->querySubObject("ActiveWorkBook");
		if (!_work_book)
			return false;

		_work_sheets = _work_book->querySubObject("sheets");
		if (!_work_sheets)
			return false;
		_work_sheet = _work_sheets->querySubObject("Item(int)", 1);
		if (!_work_sheet)
			return false;

		_status |= LExcelOpen;
		return true;
	}

	QVariant LExcel::getValue(LCell cell_idx)
	{
		if (!(_status & LExcelOpen))
			return false;

		QAxObject *cell = _work_sheet->querySubObject("Cells(int,int)", cell_idx._row, cell_idx._column);
		return cell->property("Value");
	}

	QVariant LExcel::getValue(UInt row, UInt column)
	{
		return getValue(LCell(row, column));
	}

	bool LExcel::save()
	{
		if (!(_status & LExcelOpen) || (_status & LExcelNewExcel))
			return false;

		_work_book->dynamicCall("Save()");
		return true;
	}

	bool LExcel::saveAs(const QString& path)
	{
		if (!(_status & LExcelOpen))
			return false;

		QVariant success = _work_book->dynamicCall("SaveAs(const QString&)", path);
		return success.toInt();
	}

	bool LExcel::setValue(LCell cellPlace, const QVariant& value)
	{
		if (!(_status & LExcelOpen))
			return false;

		QAxObject* cell = _work_sheet->querySubObject("Cells(int,int)", cellPlace._row, cellPlace._column);
		bool flg = cell->setProperty("Value", value);
		delete cell;
		return flg;
	}

	bool LExcel::setValue(UInt row, UInt column, const QVariant& value)
	{
		return setValue(LCell(row, column), value);
	}

	bool LExcel::setValue(UInt cell1_row, UInt cell1_column, UInt cell2_row, UInt cell2_column, const QVariant&value)
	{
		return setValue(LCell(cell1_row, cell1_column), LCell(cell2_row, cell2_column), value);
	}

	bool LExcel::setValue(LCell cellStart, LCell cellEnd, const QVariant& value)
	{
		if (!(_status & LExcelOpen))
			return false;

		QString merge_cell;
		merge_cell.append(QChar(cellStart._column - 1 + 'A'));  //初始列
		merge_cell.append(QString::number(cellStart._row));  //初始行
		merge_cell.append(":");
		merge_cell.append(QChar(cellEnd._column - 1 + 'A'));  //终止列
		merge_cell.append(QString::number(cellEnd._row));  //终止行
		QAxObject *merge_range = _work_sheet->querySubObject("Range(const QString&)", merge_cell);
		bool flg = merge_range->setProperty("Value", value);

		delete merge_range;
		return flg;
	}

	LExcel::~LExcel()
	{
		_excel->dynamicCall("Quit(void)");
	}

	bool LExcel::close()
	{
		if (!(_status & LExcelOpen))
			return false;
		_work_book->dynamicCall("Close(Boolean)", false);
		_status &= ~LExcelOpen;
		return true;
	}

	QString LExcel::numColumnToString(UInt column)
	{
		if (column <= 26)
		{
			uint num = column;
			return QString("%1").arg(QChar(num - 1 + 'A'));
		}

		QString return_str;
		int bit_num(0);
		while (1)
		{
			uint base = pow(26, bit_num);
			if (column % base == column)
				break;
			++bit_num;
		}
		--bit_num;

		std::vector<uint>bit_num_list;
		while (bit_num >= 0)
		{
			uint pow_tmp = pow(26, bit_num);
			bit_num_list.push_back(column / pow_tmp);
			column -= pow_tmp*(column / pow_tmp);
			--bit_num;
		}

		if (bit_num_list.size() == 3)
		{
			int i = 0;
			++i;
			i = i = 4;
		}

		for (int bit_num_str = bit_num_list.size() - 1; bit_num_str >= 0; --bit_num_str)
		{
			if (bit_num_list[bit_num_str] == 0)
			{
				--bit_num_list[bit_num_str - 1];
				return_str.insert(0, QChar('Z'));
				continue;
			}
			return_str.insert(0, QChar(bit_num_list[bit_num_str] - 1 + 'A'));
		}
		return return_str;
	}


	UInt LExcel::getStartRowNum(UInt item)
	{
		if (!(_status & LExcelOpen))
			return false;
		if (item == 0 || item > SheetCount())
			return false;

		QAxObject *sheet = getSheet(item);
		if (!sheet)
			return 0;

		QAxObject *used_range = sheet->querySubObject("UsedRange");
		return used_range->property("Row").toInt();  //获取起始行   
	}

	UInt LExcel::getStartColumn(UInt item)
	{
		if (!(_status & LExcelOpen))
			return false;
		if (item == 0 || item > SheetCount())
			return false;

		QAxObject *sheet = getSheet(item);
		if (!sheet)
			return 0;

		QAxObject *used_range = sheet->querySubObject("UsedRange");
		return 	used_range->property("Column").toInt();
	}

	UInt LExcel::getRowCount(UInt item)
	{
		if (!(_status & LExcelOpen))
			return false;
		if (item == 0 || item > SheetCount())
			return false;

		QAxObject *sheet = getSheet(item);
		if (!sheet)
			return 0;

		QAxObject *used_range = sheet->querySubObject("UsedRange");
		QAxObject *rows = used_range->querySubObject("Rows");
		return rows->property("Count").toInt();  //获取行数
	}

	UInt LExcel::getColumnCount(UInt item)
	{
		if (!(_status & LExcelOpen))
			return false;
		if (item == 0 || item > SheetCount())
			return false;

		QAxObject *sheet = getSheet(item);
		if (!sheet)
			return 0;

		QAxObject *used_range = sheet->querySubObject("UsedRange");
		QAxObject *columns = used_range->querySubObject("Columns");
		return columns->property("Count").toInt();  //获取列数
	}

}