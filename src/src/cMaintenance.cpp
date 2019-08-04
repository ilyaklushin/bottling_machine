#include "../include/cMaintenance.h"

cMaintenance::cMaintenance(int *_tankLevel, bool *_max)
{
	// Копирование указателей
	tankLevel = _tankLevel;
	max = _max;

	// lMoney = new Gtk::Label();
	// lMoney->override_font(*font_desc);
	// lMoney->set_xalign(1);

	// lLiters = new Gtk::Label();
	// lLiters->override_font(*font_desc);
	// lLiters->set_xalign(1);
	// lLiters->set_margin_right(35);

	// Gtk::Label *ltMoney = new Gtk::Label("На счету:");
	// ltMoney->set_xalign(0);
	// ltMoney->override_font(*font_desc);

	// Gtk::Label *ltLiters = new Gtk::Label("Литры:");
	// ltLiters->set_xalign(0);
	// ltLiters->override_font(*font_desc);

	// Gtk::Box * pPackBox1 = new Gtk::Box();
	// pPackBox1->set_orientation(Gtk::ORIENTATION_VERTICAL);
	// pPackBox1->pack_start(*ltMoney, Gtk::PACK_EXPAND_WIDGET);
	// pPackBox1->pack_start(*ltLiters,Gtk::PACK_EXPAND_WIDGET);

	// Gtk::Box * pPackBox2 = new Gtk::Box();
	// pPackBox2->set_orientation(Gtk::ORIENTATION_VERTICAL);
	// pPackBox2->pack_start(*lMoney, Gtk::PACK_EXPAND_WIDGET);
	// pPackBox2->pack_start(*lLiters,Gtk::PACK_EXPAND_WIDGET);

	//   pack_start(*pPackBox1, Gtk::PACK_SHRINK, 10);
	//   pack_start(*pPackBox2, Gtk::PACK_EXPAND_WIDGET, 10);



	// Настройка блока cMaintenance
	set_orientation(Gtk::ORIENTATION_VERTICAL);
	
	// Шрифт
	Pango::FontDescription *font = new Pango::FontDescription();
	font->set_size(12 * Pango::SCALE);
	font->set_weight(Pango::WEIGHT_LIGHT);

	// Заголовок
	Gtk::Box * pHeader = new Gtk::Box();
	
	Gtk::Label *ltMaintenanceMode = new Gtk::Label("Maintenance mode: ");
	ltMaintenanceMode->set_xalign(1);
	ltMaintenanceMode->override_font(*font);
	pHeader->pack_start(*ltMaintenanceMode, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lMaintenanceMode = new Gtk::Label("Sensors");
	lMaintenanceMode->set_xalign(0);
	lMaintenanceMode->override_font(*font);
	pHeader->pack_start(*lMaintenanceMode,Gtk::PACK_EXPAND_WIDGET);
	
	pack_start(*pHeader, Gtk::PACK_SHRINK, 10);

	// Основной
	Gtk::Box * pMain = new Gtk::Box();

	// Первый блок уровень бака
	Gtk::Box * tankBlock = new Gtk::Box();
	tankBlock->set_orientation(Gtk::ORIENTATION_VERTICAL);
	
	// Tank level
	Gtk::Box * pTankLevel = new Gtk::Box();
	
	Gtk::Label *ltTankLevel = new Gtk::Label("Tank level: ");
	ltTankLevel->set_xalign(1);
	ltTankLevel->override_font(*font);
	pTankLevel->pack_start(*ltTankLevel, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lTankLevel = new Gtk::Label("5%");
	lTankLevel->set_xalign(0);
	lTankLevel->override_font(*font);
	pTankLevel->pack_start(*lTankLevel, Gtk::PACK_EXPAND_WIDGET);
	
	tankBlock->pack_start(*pTankLevel, Gtk::PACK_EXPAND_PADDING);

	// max
	Gtk::Box * pMax = new Gtk::Box();
	
	Gtk::Label *ltMax = new Gtk::Label("max: ");
	ltMax->set_xalign(1);
	ltMax->override_font(*font);
	pMax->pack_start(*ltMax, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lMax = new Gtk::Label("f");
	lMax->set_xalign(0);
	lMax->override_font(*font);
	pMax->pack_start(*lMax, Gtk::PACK_EXPAND_WIDGET);
	
	tankBlock->pack_start(*pMax, Gtk::PACK_EXPAND_PADDING);

	// mid
	Gtk::Box * pMid = new Gtk::Box();
	
	Gtk::Label *ltMid = new Gtk::Label("mid: ");
	ltMid->set_xalign(1);
	ltMid->override_font(*font);
	pMid->pack_start(*ltMid, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lMid = new Gtk::Label("true");
	lMid->set_xalign(0);
	lMid->override_font(*font);
	pMid->pack_start(*lMid, Gtk::PACK_EXPAND_WIDGET);
	
	tankBlock->pack_start(*pMid, Gtk::PACK_EXPAND_PADDING);

	// min
	Gtk::Box * pMin = new Gtk::Box();
	
	Gtk::Label *ltMin = new Gtk::Label("min: ");
	ltMin->set_xalign(1);
	ltMin->override_font(*font);
	pMin->pack_start(*ltMin, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lMin = new Gtk::Label("false");
	lMin->set_xalign(0);
	lMin->override_font(*font);
	pMin->pack_start(*lMin, Gtk::PACK_EXPAND_WIDGET);
	
	tankBlock->pack_start(*pMin, Gtk::PACK_EXPAND_PADDING);

	// in
	Gtk::Box * pIn = new Gtk::Box();
	
	Gtk::Label *ltIn = new Gtk::Label("in: ");
	ltIn->set_xalign(1);
	ltIn->override_font(*font);
	pIn->pack_start(*ltIn, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lIn = new Gtk::Label("25 lph");
	lIn->set_xalign(0);
	lIn->override_font(*font);
	pIn->pack_start(*lIn, Gtk::PACK_EXPAND_WIDGET);
	
	tankBlock->pack_start(*pIn, Gtk::PACK_EXPAND_PADDING);

	// out
	Gtk::Box * pOut = new Gtk::Box();
	
	Gtk::Label *ltOut = new Gtk::Label("out: ");
	ltOut->set_xalign(1);
	ltOut->override_font(*font);
	pOut->pack_start(*ltOut, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lOut = new Gtk::Label("250 lph");
	lOut->set_xalign(0);
	lOut->override_font(*font);
	pOut->pack_start(*lOut, Gtk::PACK_EXPAND_WIDGET);
	
	tankBlock->pack_start(*pOut, Gtk::PACK_EXPAND_PADDING);

	pMain->pack_start(*tankBlock, Gtk::PACK_EXPAND_WIDGET);



	// Второй блок состояние выходов
	Gtk::Box * outputStatusBlock = new Gtk::Box();
	outputStatusBlock->set_orientation(Gtk::ORIENTATION_VERTICAL);
	
	// Output status
	Gtk::Box * pOutputStatus = new Gtk::Box();
	
	Gtk::Label *ltOutputStatus = new Gtk::Label("Output status");
	ltOutputStatus->override_font(*font);
	pOutputStatus->pack_start(*ltOutputStatus, Gtk::PACK_EXPAND_WIDGET);

	outputStatusBlock->pack_start(*pOutputStatus, Gtk::PACK_EXPAND_PADDING);

	// Output pump relay
	Gtk::Box * pOutputPumpRelay = new Gtk::Box();
	
	Gtk::Label *ltOutputPumpRelay = new Gtk::Label("Output pump relay: ");
	ltOutputPumpRelay->set_xalign(1);
	ltOutputPumpRelay->override_font(*font);
	pOutputPumpRelay->pack_start(*ltOutputPumpRelay, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lOutputPumpRelay = new Gtk::Label("false");
	lOutputPumpRelay->set_xalign(0);
	lOutputPumpRelay->override_font(*font);
	pOutputPumpRelay->pack_start(*lOutputPumpRelay, Gtk::PACK_EXPAND_WIDGET);
	
	outputStatusBlock->pack_start(*pOutputPumpRelay, Gtk::PACK_EXPAND_PADDING);

	// Filtration relay
	Gtk::Box * pFiltrationRelay = new Gtk::Box();
	
	Gtk::Label *ltFiltrationRelay = new Gtk::Label("Filtration relay: ");
	ltFiltrationRelay->set_xalign(1);
	ltFiltrationRelay->override_font(*font);
	pFiltrationRelay->pack_start(*ltFiltrationRelay, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lFiltrationRelay = new Gtk::Label("true");
	lFiltrationRelay->set_xalign(0);
	lFiltrationRelay->override_font(*font);
	pFiltrationRelay->pack_start(*lFiltrationRelay, Gtk::PACK_EXPAND_WIDGET);
	
	outputStatusBlock->pack_start(*pFiltrationRelay, Gtk::PACK_EXPAND_PADDING);

	// Cleaning relay
	Gtk::Box * pCleaningRelay = new Gtk::Box();
	
	Gtk::Label *ltCleaningRelay = new Gtk::Label("Cleaning relay: ");
	ltCleaningRelay->set_xalign(1);
	ltCleaningRelay->override_font(*font);
	pCleaningRelay->pack_start(*ltCleaningRelay, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lCleaningRelay = new Gtk::Label("false");
	lCleaningRelay->set_xalign(0);
	lCleaningRelay->override_font(*font);
	pCleaningRelay->pack_start(*lCleaningRelay, Gtk::PACK_EXPAND_WIDGET);
	
	outputStatusBlock->pack_start(*pCleaningRelay, Gtk::PACK_EXPAND_PADDING);

	// Heating relay
	Gtk::Box * pHeatingRelay = new Gtk::Box();
	
	Gtk::Label *ltHeatingRelay = new Gtk::Label("Heating relay: ");
	ltHeatingRelay->set_xalign(1);
	ltHeatingRelay->override_font(*font);
	pHeatingRelay->pack_start(*ltHeatingRelay, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lHeatingRelay = new Gtk::Label("false");
	lHeatingRelay->set_xalign(0);
	lHeatingRelay->override_font(*font);
	pHeatingRelay->pack_start(*lHeatingRelay, Gtk::PACK_EXPAND_WIDGET);
	
	outputStatusBlock->pack_start(*pHeatingRelay, Gtk::PACK_EXPAND_PADDING);

	// Solenoid lock
	Gtk::Box * pSolenoidLock = new Gtk::Box();
	
	Gtk::Label *ltSolenoidLock = new Gtk::Label("Solenoid lock: ");
	ltSolenoidLock->set_xalign(1);
	ltSolenoidLock->override_font(*font);
	pSolenoidLock->pack_start(*ltSolenoidLock, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lSolenoidLock = new Gtk::Label("false");
	lSolenoidLock->set_xalign(0);
	lSolenoidLock->override_font(*font);
	pSolenoidLock->pack_start(*lSolenoidLock, Gtk::PACK_EXPAND_WIDGET);
	
	outputStatusBlock->pack_start(*pSolenoidLock, Gtk::PACK_EXPAND_PADDING);

	// Coin validator pwr
	Gtk::Box * pCoinValidatorPwr = new Gtk::Box();
	
	Gtk::Label *ltCoinValidatorPwr = new Gtk::Label("Coin validator pwr: ");
	ltCoinValidatorPwr->set_xalign(1);
	ltCoinValidatorPwr->override_font(*font);
	pCoinValidatorPwr->pack_start(*ltCoinValidatorPwr, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lCoinValidatorPwr = new Gtk::Label("true");
	lCoinValidatorPwr->set_xalign(0);
	lCoinValidatorPwr->override_font(*font);
	pCoinValidatorPwr->pack_start(*lCoinValidatorPwr, Gtk::PACK_EXPAND_WIDGET);
	
	outputStatusBlock->pack_start(*pCoinValidatorPwr, Gtk::PACK_EXPAND_PADDING);

	pMain->pack_start(*outputStatusBlock, Gtk::PACK_EXPAND_WIDGET);




	// Третий блок состояние входов
	Gtk::Box * inputStatusBlock = new Gtk::Box();
	inputStatusBlock->set_orientation(Gtk::ORIENTATION_VERTICAL);
	
	// Output status
	Gtk::Box * pInputStatus = new Gtk::Box();
	
	Gtk::Label *ltInputStatus = new Gtk::Label("Output status");
	ltInputStatus->override_font(*font);
	pInputStatus->pack_start(*ltInputStatus, Gtk::PACK_EXPAND_WIDGET);

	inputStatusBlock->pack_start(*pInputStatus, Gtk::PACK_EXPAND_PADDING);

	// Temperature
	Gtk::Box * pTemperature = new Gtk::Box();
	
	Gtk::Label *ltTemperature = new Gtk::Label("Temperature: ");
	ltTemperature->set_xalign(1);
	ltTemperature->override_font(*font);
	pTemperature->pack_start(*ltTemperature, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lTemperature = new Gtk::Label("21.5 °C");
	lTemperature->set_xalign(0);
	lTemperature->override_font(*font);
	pTemperature->pack_start(*lTemperature, Gtk::PACK_EXPAND_WIDGET);
	
	inputStatusBlock->pack_start(*pTemperature, Gtk::PACK_EXPAND_PADDING);

	// Coins
	Gtk::Box * pCoins = new Gtk::Box();
	
	Gtk::Label *ltCoins = new Gtk::Label("Coins: ");
	ltCoins->set_xalign(1);
	ltCoins->override_font(*font);
	pCoins->pack_start(*ltCoins, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lCoins = new Gtk::Label("000.000");
	lCoins->set_xalign(0);
	lCoins->override_font(*font);
	pCoins->pack_start(*lCoins, Gtk::PACK_EXPAND_WIDGET);
	
	inputStatusBlock->pack_start(*pCoins, Gtk::PACK_EXPAND_PADDING);

	// Water counter
	Gtk::Box * pWaterCounter = new Gtk::Box();
	
	Gtk::Label *ltWaterCounter = new Gtk::Label("Water counter: ");
	ltWaterCounter->set_xalign(1);
	ltWaterCounter->override_font(*font);
	pWaterCounter->pack_start(*ltWaterCounter, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lWaterCounter = new Gtk::Label("00.00 lpm");
	lWaterCounter->set_xalign(0);
	lWaterCounter->override_font(*font);
	pWaterCounter->pack_start(*lWaterCounter, Gtk::PACK_EXPAND_WIDGET);
	
	inputStatusBlock->pack_start(*pWaterCounter, Gtk::PACK_EXPAND_PADDING);

	// Buttons
	Gtk::Box * pButtons = new Gtk::Box();
	
	Gtk::Label *ltButtons = new Gtk::Label("Buttons: ");
	ltButtons->set_xalign(1);
	ltButtons->override_font(*font);
	pButtons->pack_start(*ltButtons, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lButtons = new Gtk::Label("000");
	lButtons->set_xalign(0);
	lButtons->override_font(*font);
	pButtons->pack_start(*lButtons, Gtk::PACK_EXPAND_WIDGET);
	
	inputStatusBlock->pack_start(*pButtons, Gtk::PACK_EXPAND_PADDING);

	// SensorsExt
	Gtk::Box * pSensorsExt = new Gtk::Box();
	
	Gtk::Label *ltSensorsExt = new Gtk::Label("SensorsExt: ");
	ltSensorsExt->set_xalign(1);
	ltSensorsExt->override_font(*font);
	pSensorsExt->pack_start(*ltSensorsExt, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lSensorsExt = new Gtk::Label("false");
	lSensorsExt->set_xalign(0);
	lSensorsExt->override_font(*font);
	pSensorsExt->pack_start(*lSensorsExt, Gtk::PACK_EXPAND_WIDGET);
	
	inputStatusBlock->pack_start(*pSensorsExt, Gtk::PACK_EXPAND_PADDING);

	// Ranging mod
	Gtk::Box * pRangingMod = new Gtk::Box();
	
	Gtk::Label *ltRangingMod = new Gtk::Label("Ranging mod: ");
	ltRangingMod->set_xalign(1);
	ltRangingMod->override_font(*font);
	pRangingMod->pack_start(*ltRangingMod, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lRangingMod = new Gtk::Label("0000 mm");
	lRangingMod->set_xalign(0);
	lRangingMod->override_font(*font);
	pRangingMod->pack_start(*lRangingMod, Gtk::PACK_EXPAND_WIDGET);
	
	inputStatusBlock->pack_start(*pRangingMod, Gtk::PACK_EXPAND_PADDING);

	// Watch Dog
	Gtk::Box * pWatchDog = new Gtk::Box();
	
	Gtk::Label *ltWatchDog = new Gtk::Label("Watch Dog: ");
	ltWatchDog->set_xalign(1);
	ltWatchDog->override_font(*font);
	pWatchDog->pack_start(*ltWatchDog, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lWatchDog = new Gtk::Label("true");
	lWatchDog->set_xalign(0);
	lWatchDog->override_font(*font);
	pWatchDog->pack_start(*lWatchDog, Gtk::PACK_EXPAND_WIDGET);
	
	inputStatusBlock->pack_start(*pWatchDog, Gtk::PACK_EXPAND_PADDING);

	// Last keepalive
	Gtk::Box * pLastKeepalive = new Gtk::Box();
	
	Gtk::Label *ltLastKeepalive = new Gtk::Label("Last keepalive: ");
	ltLastKeepalive->set_xalign(1);
	ltLastKeepalive->override_font(*font);
	pLastKeepalive->pack_start(*ltLastKeepalive, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lLastKeepalive = new Gtk::Label("true");
	lLastKeepalive->set_xalign(0);
	lLastKeepalive->override_font(*font);
	pLastKeepalive->pack_start(*lLastKeepalive, Gtk::PACK_EXPAND_WIDGET);
	
	inputStatusBlock->pack_start(*pLastKeepalive, Gtk::PACK_EXPAND_PADDING);

	pMain->pack_start(*inputStatusBlock, Gtk::PACK_EXPAND_WIDGET);




	pack_start(*pMain, Gtk::PACK_SHRINK, 10);

	// Подвал
	Gtk::Box * pFooter = new Gtk::Box();
	
	// Дата
	Gtk::Box * pDate = new Gtk::Box();
	
	Gtk::Label *ltDate = new Gtk::Label("Date: ");
	ltDate->set_xalign(1);
	ltDate->override_font(*font);
	pDate->pack_start(*ltDate, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lDate = new Gtk::Label("12.05.2019 13:00");
	lDate->set_xalign(0);
	lDate->override_font(*font);
	pDate->pack_start(*lDate, Gtk::PACK_EXPAND_WIDGET);
	
	pFooter->pack_start(*pDate, Gtk::PACK_EXPAND_PADDING);

	// Пустой блок

	Gtk::Box * pEmpty = new Gtk::Box();
	pFooter->pack_start(*pEmpty, Gtk::PACK_EXPAND_WIDGET);
	
	// Идентификатор аппарата
	Gtk::Box * pMachineID = new Gtk::Box();
	
	Gtk::Label *ltMachineID = new Gtk::Label("machine id: ");
	ltMachineID->set_xalign(1);
	ltMachineID->override_font(*font);
	pMachineID->pack_start(*ltMachineID, Gtk::PACK_EXPAND_WIDGET);

	Gtk::Label *lMachineID = new Gtk::Label("407");
	lMachineID->set_xalign(0);
	lMachineID->override_font(*font);
	pMachineID->pack_start(*lMachineID, Gtk::PACK_EXPAND_WIDGET);
	
	pFooter->pack_start(*pMachineID, Gtk::PACK_EXPAND_PADDING);

	pack_end(*pFooter, Gtk::PACK_SHRINK, 10);

	// Показать все блоки
	show_all();
}

cMaintenance::~cMaintenance()
{
	delete tankLevel;
	delete max;

	delete lTankLevel;
	delete lMax;
}

void cMaintenance::updateCounters()
{
	//lMoney->set_text(string(*money) + "₽");
    
    lTankLevel->set_text(to_string(*tankLevel) + "%");
    lMax->set_text(to_string(*max));
    //lTankLevel->set_text("");
    //lMax->set_text("");
} 