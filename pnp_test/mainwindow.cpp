#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QMessageBox"
#include "QTime"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);  // Do not delete this

  baud_rate_[0] = 57600;
  baud_rate_[1] = 115200;
  baud_rate_[2] = 1000000;
  baud_rate_[3] = 2000000;
  baud_rate_[4] = 3000000;

  ui->read_write_button->setText("Single Read/Write");
  ui->bulk_read_write_button->setText("Multi Read/Write");

  ui->radioButton_57600->setDisabled(true);
  ui->radioButton_115200->setDisabled(true);
  ui->radioButton_1000000->setDisabled(true);
  ui->radioButton_2000000->setDisabled(true);
  ui->radioButton_3000000->setDisabled(true);

  if (openPort(DEVICE_NAME) == false)
    this->~MainWindow();

  if (setProtocolVersion(2.0) == false)
    this->~MainWindow();

  initBulkRead();
  initBulkWrite();
}

MainWindow::~MainWindow()
{
  delete ui;
}

bool MainWindow::openPort(const char* device_name)
{
  portHandler_ = dynamixel::PortHandler::getPortHandler(device_name);

  if (portHandler_->openPort())
  {
    printf("\nSucceeded to open the port(%s)!\n", device_name);

    return true;
  }
  else
  {
    printf("Failed to open the port!\n");

    return false;
  }
}

bool MainWindow::setProtocolVersion(float version)
{
  packetHandler_ = dynamixel::PacketHandler::getPacketHandler(version);

  if (packetHandler_->getProtocolVersion())
  {
    printf("Succeeded to setPacketHandler_!\n");

    return true;
  }
  else
  {
    printf("Failed to setPacketHandler_1!\n");

    return false;
  }
}

bool MainWindow::setBaudrate(uint32_t baud)
{
  if (portHandler_->setBaudRate(baud))
  {
    printf("Succeeded to change the baudrate(%d)!\n", portHandler_->getBaudRate());

    return true;
  }
  else
  {
    printf("Failed to change the baudrate!\n");

    return false;
  }
}

void MainWindow::initBulkWrite()
{
  groupBulkWrite_ = new dynamixel::GroupBulkWrite(portHandler_, packetHandler_);
}

bool MainWindow::addBulkWriteParam(uint8_t id, const char *item_name, int32_t data)
{
  bool dxl_addparam_result = false;
  uint8_t data_byte[4] = {0, };

  ControlTableItem *cti;
  cti = tools_[findTools(id)].getControlItem(item_name);

  data_byte[0] = DXL_LOBYTE(DXL_LOWORD(data));
  data_byte[1] = DXL_HIBYTE(DXL_LOWORD(data));
  data_byte[2] = DXL_LOBYTE(DXL_HIWORD(data));
  data_byte[3] = DXL_HIBYTE(DXL_HIWORD(data));

  dxl_addparam_result = groupBulkWrite_->addParam(id, cti->address, cti->data_length, data_byte);
  if (dxl_addparam_result != true)
  {
    printf("[ID:%03d] groupSyncWrite addparam failed", id);
    return false;
  }

  return true;
}

bool MainWindow::bulkWrite()
{
  int dxl_comm_result = COMM_TX_FAIL;

  dxl_comm_result = groupBulkWrite_->txPacket();
  if (dxl_comm_result != COMM_SUCCESS)
  {
    printf("%s\n", packetHandler_->getTxRxResult(dxl_comm_result));
    return false;
  }

  groupBulkWrite_->clearParam();

  return true;
}

void MainWindow::initBulkRead()
{
  groupBulkRead_ = new dynamixel::GroupBulkRead(portHandler_, packetHandler_);
}

bool MainWindow::addBulkReadParam(uint8_t id, const char *item_name)
{
  bool dxl_addparam_result = false;

  ControlTableItem *cti;
  cti = tools_[findTools(id)].getControlItem(item_name);

  dxl_addparam_result = groupBulkRead_->addParam(id, cti->address, cti->data_length);
  if (dxl_addparam_result != true)
  {
    printf("[ID:%03d] groupBulkRead addparam failed\n", id);
    return false;
  }

  return true;
}

bool MainWindow::sendBulkReadPacket()
{
  int dxl_comm_result = COMM_RX_FAIL;

  dxl_comm_result = groupBulkRead_->txRxPacket();
  if (dxl_comm_result != COMM_SUCCESS)
  {
    printf("%s\n", packetHandler_->getTxRxResult(dxl_comm_result));
    return false;
  }

  return true;
}

int32_t MainWindow::bulkRead(uint8_t id, const char *item_name)
{
  bool dxl_getdata_result = false;
  ControlTableItem *cti;
  cti = tools_[findTools(id)].getControlItem(item_name);

  dxl_getdata_result = groupBulkRead_->isAvailable(id, cti->address, cti->data_length);
  if (dxl_getdata_result != true)
  {
    printf("[ID:%03d] groupBulkRead getdata failed\n", id);
    return false;
  }

  return groupBulkRead_->getData(id, cti->address, cti->data_length);
}

void MainWindow::on_connect_pushButton_clicked()
{ 
  uint8_t error = 0;
  uint8_t id = 0;
  uint16_t model_num = 0;
  uint8_t baud_rate_index = 0;

  while (baud_rate_index < BAUDRATE_NUM)
  {
    setBaudrate(baud_rate_[baud_rate_index]);

    for (id = 1; id <= 110; id++)
    {
      ui->begin_progressBar->setValue(id);
      if (packetHandler_->ping(portHandler_, id, &model_num, &error) == COMM_SUCCESS)
      {
        get_id_[tools_cnt_] = id;

        tools_[tools_cnt_].begin(model_num);
        tools_[tools_cnt_].setID(id);

        tools_cnt_++;
      }
    }

    if (tools_cnt_ != 0)
      break;

    baud_rate_index++;
  }

  if (tools_cnt_ != 0)
  {
    QMessageBox::about(this, tr("INFO"),tr("<h2>DYNAMIXEL</h2><p>Initialization Succeed!!</p>"));

    for (int index = 0; index < tools_cnt_; index++)
    {
      int32_t present_position = 0;

      present_position = readPosition(get_id_[index]);

      float rad = convertValue2Radian(get_id_[index], present_position);

      if (index == 0)
      {
        ui->id_1_position_lineedit->setText(QString::number(RAD2DEG(rad)));;
      }
      else if (index == 1)
      {
        ui->id_2_position_lineedit->setText(QString::number(RAD2DEG(rad)));
      }
    }

    ui->radioButton_57600->setDisabled(false);
    ui->radioButton_115200->setDisabled(false);
    ui->radioButton_1000000->setDisabled(false);
    ui->radioButton_2000000->setDisabled(false);
    ui->radioButton_3000000->setDisabled(false);

    if (baud_rate_index == 0)
      ui->radioButton_57600->setChecked(true);
    else if (baud_rate_index == 1)
      ui->radioButton_115200->setChecked(true);
    else if (baud_rate_index == 2)
      ui->radioButton_1000000->setChecked(true);
    else if (baud_rate_index == 3)
      ui->radioButton_2000000->setChecked(true);
    else if (baud_rate_index == 4)
      ui->radioButton_3000000->setChecked(true);

    ui->connect_pushButton->setDisabled(true);
  }
  else
  {
    QMessageBox::about(this, tr("ERROR"),tr("<h2>DYNAMIXEL</h2><p>Initialization Failed!!</p>"));
  }
}

void MainWindow::on_read_write_button_clicked()
{
  jointMode(get_id_[0], 200, 50);

  static int index = 0;
  int32_t present_position = 0;
  float goal_degree[2] = {90.0, -90.0};

  QTime t;
  t.start();

  while (t.elapsed() < 5 * 1000) // 5 seconds
  {
    uint16_t goal_position = convertRadian2Value(get_id_[0], DEG2RAD(goal_degree[index]));
    goalPosition(get_id_[0], goal_degree[index]);

    do
    {
      present_position = readPosition(get_id_[0]);

      float rad = convertValue2Radian(get_id_[0], present_position);

      ui->id_1_position_lineedit->setText(QString::number(RAD2DEG(rad)));

    }while(abs(goal_position - present_position) > 5);

    if (index == 0)
      index = 1;
    else
      index = 0;
  }

  torque(get_id_[0], false);
}

void MainWindow::on_bulk_read_write_button_clicked()
{
  jointMode(get_id_[0], 200, 50);
  jointMode(get_id_[1], 200, 50);

  static int index = 0;
  int32_t present_position[2] = {0, 0};
  float goal_degree[2] = {90.0, -90.0};
  float rad = 0.0;

  addBulkReadParam(get_id_[0], "Present Position");
  addBulkReadParam(get_id_[1], "Present Position");

  QTime t;
  t.start();

  while (t.elapsed() < 5 * 1000) // 5 seconds
  {
    uint16_t goal_position = convertRadian2Value(get_id_[0], DEG2RAD(goal_degree[index]));
    addBulkWriteParam(get_id_[0], "Goal Position", goal_position);
    addBulkWriteParam(get_id_[1], "Goal Position", goal_position);

    bulkWrite();

    do
    {
      sendBulkReadPacket();

      present_position[0] = bulkRead(get_id_[0], "Present Position");
      present_position[1] = bulkRead(get_id_[1], "Present Position");

      rad = convertValue2Radian(get_id_[index], present_position[0]);
      ui->id_1_position_lineedit->setText(QString::number(RAD2DEG(rad)));

      rad = convertValue2Radian(get_id_[index], present_position[1]);
      ui->id_2_position_lineedit->setText(QString::number(RAD2DEG(rad)));

    }while((abs(goal_position - present_position[0]) > 5) && (abs(goal_position - present_position[1]) > 5));

    if (index == 0)
      index = 1;
    else
      index = 0;
  }

  torque(get_id_[0], false);
  torque(get_id_[1], false);
}

uint8_t MainWindow::findTools(uint8_t id)
{
  for (int i = 0; i < tools_cnt_; i++)
  {
    if (tools_[i].getID() == id)
    {
      return i;
    }
  }

  return 0;
}

bool MainWindow::writeRegister(uint8_t id, const char *item_name, int32_t data)
{
  uint8_t error = 0;
  int dxl_comm_result = COMM_TX_FAIL;

  ControlTableItem *cti;
  cti = tools_[findTools(id)].getControlItem(item_name);

  if (cti->data_length == BYTE)
  {
    dxl_comm_result = packetHandler_->write1ByteTxRx(portHandler_, id, cti->address, (uint8_t)data, &error);
  }
  else if (cti->data_length == WORD)
  {
    dxl_comm_result = packetHandler_->write2ByteTxRx(portHandler_, id, cti->address, (uint16_t)data, &error);
  }
  else if (cti->data_length == DWORD)
  {
    dxl_comm_result = packetHandler_->write4ByteTxRx(portHandler_, id, cti->address, (uint32_t)data, &error);
  }

  if (dxl_comm_result == COMM_SUCCESS)
  {
    if (error != 0)
    {
      printf("%s\n", packetHandler_->getRxPacketError(error));

      return false;
    }
  }
  else
  {
    printf("%s\n", packetHandler_->getTxRxResult(dxl_comm_result));

    return false;
  }

  return true;
}

bool MainWindow::readRegister(uint8_t id, const char *item_name, int32_t *data)
{
  uint8_t error = 0;
  int dxl_comm_result = COMM_RX_FAIL;

  int8_t value_8_bit = 0;
  int16_t value_16_bit = 0;
  int32_t value_32_bit = 0;

  ControlTableItem *cti;
  cti = tools_[findTools(id)].getControlItem(item_name);

  if (cti->data_length == BYTE)
  {
    dxl_comm_result = packetHandler_->read1ByteTxRx(portHandler_, id, cti->address, (uint8_t *)&value_8_bit, &error);
  }
  else if (cti->data_length == WORD)
  {
    dxl_comm_result = packetHandler_->read2ByteTxRx(portHandler_, id, cti->address, (uint16_t *)&value_16_bit, &error);
  }
  else if (cti->data_length == DWORD)
  {
    dxl_comm_result = packetHandler_->read4ByteTxRx(portHandler_, id, cti->address, (uint32_t *)&value_32_bit, &error);
  }

  if (dxl_comm_result == COMM_SUCCESS)
  {
    if (error != 0)
    {
      printf("%s\n", packetHandler_->getRxPacketError(error));
    }

    if (cti->data_length == BYTE)
    {
      *data = value_8_bit;
    }
    else if (cti->data_length == WORD)
    {
      *data = value_16_bit;
    }
    else if (cti->data_length == DWORD)
    {
      *data = value_32_bit;
    }
  }
  else
  {
    printf("%s\n", packetHandler_->getTxRxResult(dxl_comm_result));

    return false;
  }

  return true;
}


bool MainWindow::jointMode(uint8_t id, uint16_t vel, uint16_t acc)
{
  bool error = false;
  const uint8_t position_control_mode = 3;

  torque(id, false);

  error = writeRegister(id, "Operating Mode", position_control_mode);

  torque(id, true);

  error = writeRegister(id, "Profile Acceleration", acc);
  error = writeRegister(id, "Profile Velocity", vel);

  return error;
}

bool MainWindow::torque(uint8_t id, bool onoff)
{
  bool error = false;
  error = writeRegister(id, "Torque Enable", onoff);

  return error;
}

bool MainWindow::goalPosition(uint8_t id, float deg)
{
  bool error = false;
  uint16_t goal = convertRadian2Value(get_id_[0], DEG2RAD(deg));

  error = writeRegister(id, "Goal Position", goal);

  return error;
}

int32_t MainWindow::readPosition(uint8_t id)
{
  static int32_t value = 0;

  if (readRegister(id, "Present Position", &value))
    return value;

  return 0;
}

int32_t MainWindow::readVelocity(uint8_t id)
{
  static int32_t value = 0;

  if (readRegister(id, "Present Velocity", &value))
    return value;

  return 0;
}

void MainWindow::on_close_pushButton_clicked()
{
  portHandler_->closePort();
  exit(0);
}

int32_t MainWindow::convertRadian2Value(int8_t id, float radian)
{
  int32_t value = 0;
  int8_t num = 0;

  num = findTools(id);

  if (radian > 0)
  {
    if (tools_[num].getValueOfMaxRadianPosition() <= tools_[num].getValueOfZeroRadianPosition())
      return tools_[num].getValueOfMaxRadianPosition();

    value = (radian * (tools_[num].getValueOfMaxRadianPosition() - tools_[num].getValueOfZeroRadianPosition()) / tools_[num].getMaxRadian()) + tools_[num].getValueOfZeroRadianPosition();
  }
  else if (radian < 0)
  {
    if (tools_[num].getValueOfMinRadianPosition() >= tools_[num].getValueOfZeroRadianPosition())
      return tools_[num].getValueOfMinRadianPosition();

    value = (radian * (tools_[num].getValueOfMinRadianPosition() - tools_[num].getValueOfZeroRadianPosition()) / tools_[num].getMinRadian()) + tools_[num].getValueOfZeroRadianPosition();
  }
  else
  {
    value = tools_[num].getValueOfZeroRadianPosition();
  }
  // if (value[id-1] > tools_[num].getValueOfMaxRadianPosition())
  //   value[id-1] =  tools_[num].getValueOfMaxRadianPosition();
  // else if (value[id-1] < tools_[num].getValueOfMinRadianPosition())
  //   value[id-1] =  tools_[num].getValueOfMinRadianPosition();

  return value;
}

float MainWindow::convertValue2Radian(int8_t id, int32_t value)
{
  float radian = 0.0;
  int8_t num = 0;

  num = findTools(id);

  if (value > tools_[num].getValueOfZeroRadianPosition())
  {
    if (tools_[num].getMaxRadian() <= 0)
      return tools_[num].getMaxRadian();

    radian = (float)(value - tools_[num].getValueOfZeroRadianPosition()) * tools_[num].getMaxRadian() / (float)(tools_[num].getValueOfMaxRadianPosition() - tools_[num].getValueOfZeroRadianPosition());
  }
  else if (value < tools_[num].getValueOfZeroRadianPosition())
  {
    if (tools_[num].getMinRadian() >= 0)
      return tools_[num].getMinRadian();

    radian = (float)(value - tools_[num].getValueOfZeroRadianPosition()) * tools_[num].getMinRadian() / (float)(tools_[num].getValueOfMinRadianPosition() - tools_[num].getValueOfZeroRadianPosition());
  }
  //  if (radian[id-1] > tools_[num].getMaxRadian())
  //    radian[id-1] =  tools_[num].getMaxRadian();
  //  else if (radian[id-1] < tools_[num].min_radian_)
  //    radian[id-1] =  tools_[num].min_radian_;

  return radian;
}

void MainWindow::on_radioButton_57600_clicked()
{
  int32_t baud = 57600;

  for (int index = 0; index < tools_cnt_; index++)
  {
    torque(get_id_[index], false);
    writeRegister(get_id_[index], "Baud Rate", 1);
  }

  setBaudrate(baud);
}

void MainWindow::on_radioButton_115200_clicked()
{
  int32_t baud = 115200;

  for (int index = 0; index < tools_cnt_; index++)
  {
    torque(get_id_[index], false);
    writeRegister(get_id_[index], "Baud Rate", 2);
  }

  setBaudrate(baud);
}

void MainWindow::on_radioButton_1000000_clicked()
{
  int32_t baud = 1000000;

  for (int index = 0; index < tools_cnt_; index++)
  {
    torque(get_id_[index], false);
    writeRegister(get_id_[index], "Baud Rate", 3);
  }

  setBaudrate(baud);
}

void MainWindow::on_radioButton_2000000_clicked()
{
  int32_t baud = 2000000;

  for (int index = 0; index < tools_cnt_; index++)
  {
    torque(get_id_[index], false);
    writeRegister(get_id_[index], "Baud Rate", 4);
  }

  setBaudrate(baud);
}

void MainWindow::on_radioButton_3000000_clicked()
{
  int32_t baud = 3000000;

  for (int index = 0; index < tools_cnt_; index++)
  {
    torque(get_id_[index], false);
    writeRegister(get_id_[index], "Baud Rate", 5);
  }

  setBaudrate(baud);
}
