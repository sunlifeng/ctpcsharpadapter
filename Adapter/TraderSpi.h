#pragma once

#include <vcclr.h>
#include ".\ThostTraderApi\ThostFtdcTraderApi.h"
#include "CSApiStruct.h"


using namespace System;
using namespace std;
using namespace System::Runtime::InteropServices;


namespace CTP{


	public interface class  CTPTraderSpi
	{
	public:

		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
		virtual void OnFrontConnected();

		///登录请求响应
		virtual void OnRspUserLogin(CSCThostFtdcRspUserLoginField^ pRspUserLogin,	CSCThostFtdcRspInfoField^ pRspInfo, int nRequestID, bool bIsLast);

		///投资者结算结果确认响应
		virtual void OnRspSettlementInfoConfirm(CSCThostFtdcSettlementInfoConfirmField^ pSettlementInfoConfirm, CSCThostFtdcRspInfoField^ pRspInfo, int nRequestID, bool bIsLast);

		///请求查询合约响应
		virtual void OnRspQryInstrument(CSCThostFtdcInstrumentField^ pInstrument, CSCThostFtdcRspInfoField^ pRspInfo, int nRequestID, bool bIsLast);

		///请求查询资金账户响应
		virtual void OnRspQryTradingAccount(CSCThostFtdcTradingAccountField^ pTradingAccount, CSCThostFtdcRspInfoField^ pRspInfo, int nRequestID, bool bIsLast);

		///请求查询投资者持仓响应
		virtual void OnRspQryInvestorPosition(CSCThostFtdcInvestorPositionField^ pInvestorPosition, CSCThostFtdcRspInfoField^ pRspInfo, int nRequestID, bool bIsLast);

		///报单录入请求响应
		virtual void OnRspOrderInsert(CSCThostFtdcInputOrderField^ pInputOrder, CSCThostFtdcRspInfoField^ pRspInfo, int nRequestID, bool bIsLast);

		///报单操作请求响应
		virtual void OnRspOrderAction(CSCThostFtdcInputOrderActionField^ pInputOrderAction, CSCThostFtdcRspInfoField^ pRspInfo, int nRequestID, bool bIsLast);

		///错误应答
		virtual void OnRspError(CSCThostFtdcRspInfoField^ pRspInfo, int nRequestID, bool bIsLast);

		///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
		virtual void OnFrontDisconnected(int nReason);

		///心跳超时警告。当长时间未收到报文时，该方法被调用。
		virtual void OnHeartBeatWarning(int nTimeLapse);

		///报单通知
		virtual void OnRtnOrder(CSCThostFtdcOrderField^ pOrder);

		///成交通知
		virtual void OnRtnTrade(CSCThostFtdcTradeField^ pTrade);

		//private:
		//	///用户登录请求
		//	void ReqUserLogin();
		//	///投资者结算结果确认
		//	void ReqSettlementInfoConfirm();
		//	///请求查询合约
		//	void ReqQryInstrument();
		//	///请求查询资金账户
		//	void ReqQryTradingAccount();
		//	///请求查询投资者持仓
		//	void ReqQryInvestorPosition();
		//	///报单录入请求
		//	void ReqOrderInsert();
		//	///报单操作请求
		//	void ReqOrderAction(CSCThostFtdcOrderField^ pOrder);
		//
		//	// 是否收到成功的响应
		//	bool IsErrorRspInfo(CSCThostFtdcRspInfoField^ pRspInfo);
		//	// 是否我的报单回报
		//	bool IsMyOrder(CSCThostFtdcOrderField^ pOrder);
		//	// 是否正在交易的报单
		//	bool IsTradingOrder(CSCThostFtdcOrderField^ pOrder);

	};



	public ref class CTPTraderConfig
	{
	public:
		// 配置参数 以下参数清参考原始C++ API 文档

		String  ^FRONT_ADDR;		// 前置地址
		String	 ^BROKER_ID ;		// 经纪公司代码
		String  ^INVESTOR_ID ;		// 投资者代码
		String  ^PASSWORD;			// 用户密码
		String  ^INSTRUMENT_ID;		// 合约代码
		int iInstrumentID ;	

		int iRequestID;             // 请求编号
		double	LIMIT_PRICE;        //限价
		char	DIRECTION;          //买卖方向 请参考
		CTPTraderSpi  ^ctpTraderSpi; 
	};


	class CTraderSpi : public CThostFtdcTraderSpi
	{

	public:
		// USER_API参数
		CThostFtdcTraderApi* pUserApi;

		// 配置参数
		char FRONT_ADDR[100];		// 前置地址
		char BROKER_ID[11];		// 经纪公司代码
		char INVESTOR_ID[13];		// 投资者代码
		char PASSWORD[41];			// 用户密码
		char INSTRUMENT_ID[31];	// 合约代码
		double	LIMIT_PRICE;	// 价格
		char	DIRECTION;	// 买卖方向
	
		// 请求编号
		int iRequestID;

		// 配置文件
		gcroot<CTPTraderConfig^>   ctpTraderConfig;


		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
		virtual void OnFrontConnected();

		///登录请求响应
		virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///投资者结算结果确认响应
		virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询合约响应
		virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询资金账户响应
		virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///请求查询投资者持仓响应
		virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///报单录入请求响应
		virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///报单操作请求响应
		virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///错误应答
		virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

		///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
		virtual void OnFrontDisconnected(int nReason);

		///心跳超时警告。当长时间未收到报文时，该方法被调用。
		virtual void OnHeartBeatWarning(int nTimeLapse);

		///报单通知
		virtual void OnRtnOrder(CThostFtdcOrderField *pOrder);

		///成交通知
		virtual void OnRtnTrade(CThostFtdcTradeField *pTrade);


	//private:
		///用户登录请求
		void ReqUserLogin();
		///投资者结算结果确认
		void ReqSettlementInfoConfirm();
		///请求查询合约
		void ReqQryInstrument();
		///请求查询资金账户
		void ReqQryTradingAccount();
		///请求查询投资者持仓
		void ReqQryInvestorPosition();
		///报单录入请求
		void ReqOrderInsert();
		///报单操作请求
		void ReqOrderAction(CThostFtdcOrderField *pOrder);

		// 是否收到成功的响应
		bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
		// 是否我的报单回报
		bool IsMyOrder(CThostFtdcOrderField *pOrder);
		// 是否正在交易的报单
		bool IsTradingOrder(CThostFtdcOrderField *pOrder);

	};




	public ref class CTPTraderAdapter
	{

	public:
		CThostFtdcTraderApi* pUserApi;
		CTraderSpi* pUserSpi;

		int Start()
		{
			//CThostFtdcTraderApi* pUserApi;
			pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();			// 创建UserApi
			//CTraderSpi* pUserSpi = new CTraderSpi();
			pUserSpi = new CTraderSpi();
			pUserSpi->pUserApi=pUserApi;

			pUserSpi->ctpTraderConfig=this->ctpTraderConfig;

			char* abc;
			abc=	( char*)   (Marshal::StringToHGlobalAnsi(ctpTraderConfig->FRONT_ADDR)).ToPointer();
			strcpy_s(pUserSpi->FRONT_ADDR,abc);
			abc=	( char*)   (Marshal::StringToHGlobalAnsi(ctpTraderConfig->BROKER_ID)).ToPointer();
			strcpy_s(pUserSpi->BROKER_ID,abc);
			abc=	( char*)   (Marshal::StringToHGlobalAnsi(ctpTraderConfig->INVESTOR_ID)).ToPointer();
			strcpy_s(pUserSpi->INVESTOR_ID,abc);
			abc=	( char*)   (Marshal::StringToHGlobalAnsi(ctpTraderConfig->PASSWORD)).ToPointer();
			strcpy_s(pUserSpi->PASSWORD,abc);

			pUserSpi->DIRECTION=ctpTraderConfig->DIRECTION;
			pUserSpi->iRequestID=ctpTraderConfig->iRequestID;
			abc=	( char*)   (Marshal::StringToHGlobalAnsi(ctpTraderConfig->INSTRUMENT_ID)).ToPointer();
			strcpy_s(pUserSpi->INSTRUMENT_ID,abc);
			pUserSpi->LIMIT_PRICE=ctpTraderConfig->LIMIT_PRICE;

			pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// 注册事件类
			pUserApi->SubscribePublicTopic(TERT_RESTART);					// 注册公有流
			pUserApi->SubscribePrivateTopic(TERT_RESTART);					// 注册私有流
			pUserApi->RegisterFront(( char*) (Marshal::StringToHGlobalAnsi(ctpTraderConfig->FRONT_ADDR)).ToPointer());							// connect
			pUserApi->Init();

			pUserApi->Join();
			
			return 0;
		}

		void Config(CTPTraderConfig^   ctpTraderConfig)
		{
			this->ctpTraderConfig=ctpTraderConfig;
	
		}

		///用户登录请求
		void ReqUserLogin()
		{
			pUserSpi->ReqUserLogin();
		}
		///投资者结算结果确认
		void ReqSettlementInfoConfirm()
		{
			pUserSpi->ReqSettlementInfoConfirm();
		}
		///请求查询合约
		void ReqQryInstrument()
		{
			pUserSpi->ReqQryInstrument();

		}
		///请求查询资金账户
		void ReqQryTradingAccount()
		{
			pUserSpi->ReqQryTradingAccount();
		}
		///请求查询投资者持仓
		void ReqQryInvestorPosition()
		{
			pUserSpi->ReqQryInvestorPosition();
		}
		///报单录入请求
		void ReqOrderInsert()
		{
			pUserSpi->ReqOrderInsert();
		}
		///报单操作请求
		void ReqOrderAction(CSCThostFtdcOrderField^ pOrder)
		{

		}

		// 是否收到成功的响应
		bool IsErrorRspInfo(CSCThostFtdcRspInfoField^ pRspInfo)
		{
			return true;
		}
		// 是否我的报单回报
		bool IsMyOrder(CSCThostFtdcOrderField^ pOrder)
		{
			return true;
		}
		// 是否正在交易的报单
		bool IsTradingOrder(CSCThostFtdcOrderField^ pOrder)
		{
			return true;
		}
		CTPTraderConfig^   ctpTraderConfig;

	private:


	};


}