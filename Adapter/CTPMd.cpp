// This is the main DLL file.


#include "stdafx.h"
#include "CTPMd.h"

namespace CTP {

	void CMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo,
		int nRequestID, bool bIsLast)
	{
		cerr << "--->>> "<< __FUNCTION__ << endl;
		IsErrorRspInfo(pRspInfo);
		if (ctpConfig->ctpSpi!=nullptr)
		{
			CSCThostFtdcRspInfoField cspRspInfo;
			cspRspInfo.ErrorID=pRspInfo->ErrorID;
			cspRspInfo.ErrorMsg=gcnew  String(pRspInfo->ErrorMsg);
			ctpConfig->ctpSpi->OnRspError(%cspRspInfo, nRequestID ,bIsLast);
		}
	}

	void CMdSpi::OnFrontDisconnected(int nReason)
	{
		cerr << "--->>> " << __FUNCTION__ << endl;
		cerr << "--->>> Reason = " << nReason << endl;

		if (ctpConfig->ctpSpi!=nullptr)
			ctpConfig->ctpSpi->OnFrontDisconnected(nReason);

	}

	void CMdSpi::OnHeartBeatWarning(int nTimeLapse)
	{
		cerr << "--->>> " << __FUNCTION__ << endl;
		cerr << "--->>> nTimerLapse = " << nTimeLapse << endl;
		if (ctpConfig->ctpSpi!=nullptr)
			ctpConfig->ctpSpi->OnHeartBeatWarning(nTimeLapse);
	}

	void CMdSpi::OnFrontConnected()
	{
		cerr << "--->>> " << __FUNCTION__ << endl;

		if (ctpConfig->ctpSpi!=nullptr)
			ctpConfig->ctpSpi->OnFrontConnected();
		///用户登录请求
		ReqUserLogin();

	}

	void CMdSpi::ReqUserLogin()
	{
		CThostFtdcReqUserLoginField req;
		memset(&req, 0, sizeof(req));
		strcpy_s(req.BrokerID, BROKER_ID);
		strcpy_s(req.UserID, INVESTOR_ID);
		strcpy_s(req.Password, PASSWORD);
		int iResult = pUserApi->ReqUserLogin(&req, ++iRequestID);
		cerr << "--->>> 发送用户登录请求: " << ((iResult == 0) ? "成功" : "失败") << endl;

	}

	void CMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		cerr << "--->>> " << __FUNCTION__ << endl;

		if (ctpConfig->ctpSpi!=nullptr)
		{
			CSCThostFtdcRspInfoField cspRspInfo;
			CSCThostFtdcRspUserLoginField cspRspUserLogin;

			cspRspInfo.ErrorID=pRspInfo->ErrorID;
			cspRspInfo.ErrorMsg=gcnew  String(pRspInfo->ErrorMsg);
			cspRspUserLogin.BrokerID=gcnew  String(pRspUserLogin->BrokerID);
			cspRspUserLogin.CZCETime=gcnew  String(pRspUserLogin->CZCETime);
			cspRspUserLogin.DCETime=gcnew  String(pRspUserLogin->DCETime);
			cspRspUserLogin.FFEXTime=gcnew  String(pRspUserLogin->FFEXTime);
			cspRspUserLogin.FrontID=pRspUserLogin->FrontID;
			cspRspUserLogin.LoginTime=gcnew  String(pRspUserLogin->LoginTime);
			cspRspUserLogin.MaxOrderRef=gcnew  String(pRspUserLogin->MaxOrderRef);
			cspRspUserLogin.SessionID=pRspUserLogin->SessionID;
			cspRspUserLogin.SHFETime=gcnew  String(pRspUserLogin->SHFETime);
			cspRspUserLogin.SystemName=gcnew  String(pRspUserLogin->SystemName);
			cspRspUserLogin.TradingDay=gcnew  String(pRspUserLogin->TradingDay);
			cspRspUserLogin.UserID=gcnew  String(pRspUserLogin->UserID);

			ctpConfig->ctpSpi->OnRspUserLogin(%cspRspUserLogin,%cspRspInfo, nRequestID ,bIsLast);
		}

		if (bIsLast && !IsErrorRspInfo(pRspInfo))
		{
			///获取当前交易日
			cerr << "--->>> 获取当前交易日 = " << pUserApi->GetTradingDay() << endl;
			// 请求订阅行情
			SubscribeMarketData();	
		}
	}

	void CMdSpi::SubscribeMarketData()
	{
		int iResult = pUserApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
		cerr << "--->>> 发送行情订阅请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
	}

	void CMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		//cerr << __FUNCTION__ << endl;
		if (ctpConfig->ctpSpi!=nullptr)
		{
			CSCThostFtdcRspInfoField cspRspInfo;
			CSCThostFtdcSpecificInstrumentField cspSpecificInstrument;
			cspSpecificInstrument.InstrumentID=gcnew  String(pSpecificInstrument->InstrumentID);

			cspRspInfo.ErrorID=pRspInfo->ErrorID;
			cspRspInfo.ErrorMsg=gcnew  String(pRspInfo->ErrorMsg);

			ctpConfig->ctpSpi->OnRspSubMarketData(%cspSpecificInstrument,%cspRspInfo, nRequestID ,bIsLast);
		}
	}


	void CMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		cerr << __FUNCTION__ << endl;
		if (ctpConfig->ctpSpi!=nullptr)
		{
			CSCThostFtdcRspInfoField cspRspInfo;
			CSCThostFtdcSpecificInstrumentField cspSpecificInstrument;
			cspSpecificInstrument.InstrumentID=gcnew  String(pSpecificInstrument->InstrumentID);

			cspRspInfo.ErrorID=pRspInfo->ErrorID;
			cspRspInfo.ErrorMsg=gcnew  String(pRspInfo->ErrorMsg);
			ctpConfig->ctpSpi->OnRspUnSubMarketData(%cspSpecificInstrument,%cspRspInfo, nRequestID ,bIsLast);

		}
	}

	void CMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
	{
		cerr << __FUNCTION__ << endl;
		if (ctpConfig->ctpSpi!=nullptr)
		{
			CSCThostFtdcDepthMarketDataField cspDepthMarketData;

			cspDepthMarketData.TradingDay=gcnew  String(pDepthMarketData->TradingDay);
			cspDepthMarketData.InstrumentID=gcnew  String(pDepthMarketData->InstrumentID);
			cspDepthMarketData.ExchangeID=gcnew  String(pDepthMarketData->ExchangeID);
			cspDepthMarketData.ExchangeInstID=gcnew  String(pDepthMarketData->ExchangeInstID);

			cspDepthMarketData.LastPrice=pDepthMarketData->LastPrice;
			cspDepthMarketData.PreSettlementPrice=pDepthMarketData->PreSettlementPrice;
			cspDepthMarketData.PreClosePrice=pDepthMarketData->PreClosePrice;
			cspDepthMarketData.PreOpenInterest=pDepthMarketData->PreOpenInterest;
			cspDepthMarketData.OpenPrice=pDepthMarketData->OpenPrice;
			cspDepthMarketData.HighestPrice=pDepthMarketData->HighestPrice;
			cspDepthMarketData.LowestPrice=pDepthMarketData->LowestPrice;
			cspDepthMarketData.Volume=pDepthMarketData->Volume;
			cspDepthMarketData.Turnover=pDepthMarketData->Turnover;
			cspDepthMarketData.OpenInterest=pDepthMarketData->OpenInterest;
			cspDepthMarketData.ClosePrice=pDepthMarketData->ClosePrice;
			cspDepthMarketData.SettlementPrice=pDepthMarketData->SettlementPrice;
			cspDepthMarketData.UpperLimitPrice=pDepthMarketData->UpperLimitPrice;
			cspDepthMarketData.LowerLimitPrice=pDepthMarketData->LowerLimitPrice;
			cspDepthMarketData.PreDelta=pDepthMarketData->PreDelta;
			cspDepthMarketData.CurrDelta=pDepthMarketData->CurrDelta;
			cspDepthMarketData.UpdateTime=gcnew  String(pDepthMarketData->UpdateTime);
			cspDepthMarketData.UpdateMillisec=pDepthMarketData->UpdateMillisec;

			cspDepthMarketData.BidPrice1=pDepthMarketData->BidPrice1;
			cspDepthMarketData.BidVolume1=pDepthMarketData->BidVolume1;
			cspDepthMarketData.AskPrice1=pDepthMarketData->AskPrice1;
			cspDepthMarketData.AskVolume1=pDepthMarketData->AskVolume1;

			cspDepthMarketData.BidPrice2=pDepthMarketData->BidPrice2;
			cspDepthMarketData.BidVolume2=pDepthMarketData->BidVolume2;
			cspDepthMarketData.AskPrice2=pDepthMarketData->AskPrice2;
			cspDepthMarketData.AskVolume2=pDepthMarketData->AskVolume2;

			cspDepthMarketData.BidPrice3=pDepthMarketData->BidPrice3;
			cspDepthMarketData.BidVolume3=pDepthMarketData->BidVolume3;
			cspDepthMarketData.AskPrice3=pDepthMarketData->AskPrice3;
			cspDepthMarketData.AskVolume3=pDepthMarketData->AskVolume3;

			cspDepthMarketData.BidPrice4=pDepthMarketData->BidPrice4;
			cspDepthMarketData.BidVolume4=pDepthMarketData->BidVolume4;
			cspDepthMarketData.AskPrice4=pDepthMarketData->AskPrice4;
			cspDepthMarketData.AskVolume4=pDepthMarketData->AskVolume4;

			cspDepthMarketData.BidPrice5=pDepthMarketData->BidPrice5;
			cspDepthMarketData.BidVolume5=pDepthMarketData->BidVolume5;
			cspDepthMarketData.AskPrice5=pDepthMarketData->AskPrice5;
			cspDepthMarketData.AskVolume5=pDepthMarketData->AskVolume5;

			cspDepthMarketData.AveragePrice=pDepthMarketData->AveragePrice;

			ctpConfig->ctpSpi->OnRtnDepthMarketData(%cspDepthMarketData);
		}
	}

	bool CMdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
	{
		// 如果ErrorID != 0, 说明收到了错误的响应
		bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
		if (bResult)
			cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
		return bResult;
	}


}