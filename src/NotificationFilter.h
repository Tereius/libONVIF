#pragma once
#include "OnvifEventExport.h"
#include "Response.h"
#include <QObject>
#include <QList>
#include <QVariant>


namespace Filter
{

	class Stringable {

	public:
		virtual QString toString() const = 0;
	};


	namespace Attr
	{

		class Expression : public Stringable {

		};


		class Val : public Expression {

		public:
			Val(QVariant val) :
				mVal(val) {}

			virtual QString toString() const override;

		private:
			QVariant mVal;
		};


		class And : public Expression {

		public:
			And(QList<Expression*> exList) :
				mExList(exList) {}

			virtual QString toString() const override;

		private:
			QList<Expression*> mExList;
		};


		class Or : public Expression {

		public:
			Or(QList<Expression*> exList) :
				mExList(exList) {}

			virtual QString toString() const override;

		private:
			QList<Expression*> mExList;
		};


		class Not : public Expression {

		public:
			Not(Expression* ex) :
				mEx(ex) {}

			virtual QString toString() const override;

		private:
			Expression* mEx;
		};
	}


	class SimpleItem : public Stringable {

	public:
		SimpleItem(const QString &rName, Attr::Expression* ex) :
			mName(rName),
			mEx(ex) {
		}

		virtual QString toString() const override;

	private:
		QString mName;
		Attr::Expression* mEx;
	};


	class Expression : public Stringable {

	};


	class BoolExpr : public Expression {

	public:
		BoolExpr(SimpleItem* item) :
			mItem(item) {}

		virtual QString toString() const override;

	private:
		SimpleItem* mItem;
	};


	class And : public Expression {

	public:
		And(QList<Expression*> exList) :
			mExList(exList) {}

		virtual QString toString() const override;

	private:
		QList<Expression*> mExList;
	};


	class Or : public Expression {

	public:
		Or(QList<Expression*> exList) :
			mExList(exList) {}

		virtual QString toString() const override;

	private:
		QList<Expression*> mExList;
	};


	class Not : public Expression {

	public:
		Not(Expression* ex) :
			mEx(ex) {}

		virtual QString toString() const override;

	private:
		Expression* mEx;
	};
}

class ONVIFEVENT_EXPORT NotificationFilter : public QObject {

public:
	NotificationFilter(QObject *pParent = nullptr) :
		QObject(pParent) {}

signals:
	void FilterMatched();

	public slots:
	void MessageReceived(const Response<wsnt__NotificationMessageHolderType> &rResponse);
};
