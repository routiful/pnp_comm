#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);  // Do not delete this
  qtimer_ = new QTimer;
  file_   = new QFile;

  QString filename = QTime::currentTime().toString() + QString(" COMMUNICATION TEST(ROBOTIS)");
  file_->setFileName(filename);
  file_->open(QIODevice::WriteOnly);

  baud_rate_[0] = 57600;
  baud_rate_[1] = 115200;
  baud_rate_[2] = 1000000;
  baud_rate_[3] = 2000000;
  baud_rate_[4] = 3000000;

  ui->single_read_write_button->setText("Single Read/Write");
  ui->multi_read_write_button->setText("Multi Read/Write");
  ui->all_tools_read_button->setText("All tools Read");

  ui->radioButton_57600->setDisabled(true);
  ui->radioButton_115200->setDisabled(true);
  ui->radioButton_1000000->setDisabled(true);
  ui->radioButton_2000000->setDisabled(true);
  ui->radioButton_3000000->setDisabled(true);

  if (openPort(DEVICE_NAME) == false)
  {
    QMessageBox::about(this, tr("ERROR"),tr("<h2>CONNECTION</h2><p>Can't open port!!</p>"));
    this->~MainWindow();
  }

  if (setProtocolVersion(2.0) == false)
  {
    QMessageBox::about(this, tr("ERROR"),tr("<h2>CONNECTION</h2><p>Can't set packetHandler!!</p>"));
    this->~MainWindow();
  }

  initSyncWrite();
  initSyncRead();
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

void MainWindow::initSyncWrite()
{
  dxlSyncWrite_ = new dynamixel::GroupSyncWrite(portHandler_,
                                                packetHandler_,
                                                ADDR_DYNAMIXEL_GOAL_POSITION,
                                                LEN_DYNAMIXEL_GOAL_POSITION);
}

output_info MainWindow::syncWrite(uint8_t tool_num, int32_t* data)
{
  bool dxl_addparam_result = false;
  int dxl_comm_result = COMM_TX_FAIL;
  output_info info = {false, 0};
  uint8_t data_byte[4] = {0, };
  uint8_t cnt = tool_num;
  static uint32_t t_time = 0;

  for (int num = 0; num < cnt; ++num)
  {
    data_byte[0] = DXL_LOBYTE(DXL_LOWORD(data[num]));
    data_byte[1] = DXL_HIBYTE(DXL_LOWORD(data[num]));
    data_byte[2] = DXL_LOBYTE(DXL_HIWORD(data[num]));
    data_byte[3] = DXL_HIBYTE(DXL_HIWORD(data[num]));

    dxl_addparam_result = dxlSyncWrite_->addParam(tools_[num].getID(), (uint8_t *)&data_byte);
    if (dxl_addparam_result != true)
    {
      printf("[ID:%03d] groupSyncWrite addparam failed", tools_[num].getID());

      info.error = true;
    }
  }

  t_time = micros();
  dxl_comm_result = dxlSyncWrite_->txPacket();
  info.time = micros() - t_time;

  if (dxl_comm_result != COMM_SUCCESS)
  {
    printf("%s\n", packetHandler_->getTxRxResult(dxl_comm_result));
    info.error = true;
  }
  dxlSyncWrite_->clearParam();

  return info;
}

void MainWindow::initSyncRead()
{
  dxlSyncRead_ = new dynamixel::GroupSyncRead(portHandler_,
                                              packetHandler_,
                                              ADDR_DYNAMIXEL_PRESENT_POSITION,
                                              LEN_DYNAMIXEL_PRESENT_POSITION);

  allToolsSyncRead_ = new dynamixel::GroupSyncRead(portHandler_,
                                                   packetHandler_,
                                                   ADDR_DYNAMIXEL_GOAL_POSITION,
                                                   LEN_DYNAMIXEL_GOAL_POSITION);
}

output_info MainWindow::syncRead(uint8_t tools_num, uint16_t address, uint8_t data_length, int32_t *data)
{
  int dxl_comm_result = COMM_RX_FAIL;
  bool dxl_addparam_result = false;
  bool dxl_getdata_result = false;
  output_info info = {false, 0};
  uint8_t cnt = tools_num;
  static uint32_t t_time = 0;

  for (int num = 0; num < cnt; num++)
  {
    dxl_addparam_result = dxlSyncRead_->addParam(tools_[num].getID());
    if (dxl_addparam_result != true)
      info.error = true;
  }

  t_time = micros();
  dxl_comm_result = dxlSyncRead_->txRxPacket();
  info.time = micros() - t_time;

  if (dxl_comm_result != COMM_SUCCESS)
  {
    printf("%s\n", packetHandler_->getTxRxResult(dxl_comm_result));
    info.error = true;
  }

  for (int num = 0; num < cnt; ++num)
  {
    uint8_t id = tools_[num].getID();

    dxl_getdata_result = dxlSyncRead_->isAvailable(id, address, data_length);

    if (dxl_getdata_result)
    {
      data[num] = dxlSyncRead_->getData(id, address, data_length);
    }
    else
    {
      info.error = true;
    }
  }

  dxlSyncRead_->clearParam();

  return info;
}

void MainWindow::updateData()
{
  int32_t dxl_1_present_position = 0, dxl_2_present_position = 0;
  int32_t dxl_1_present_velocity = 0, dxl_2_present_veloticy = 0;
  int32_t *imu_data, *temp_data, *color_data, *adc_data;

  for (int index = 0; index < tools_cnt_; index++)
  {
    if (get_id_[index] == DXL_1)
    {
      dxl_1_present_position = readPosition(DXL_1);
      dxl_1_present_velocity = readVelocity(DXL_1);

      showData(std::string("< DYNAMIXEL 1 >"));
      showData(std::string("present_position  : "), dxl_1_present_position);
      showData(std::string("present_velocity  : "), dxl_1_present_velocity);
      showData(std::string(" "));
    }

    if (get_id_[index] == DXL_2)
    {
      dxl_2_present_position = readPosition(DXL_2);
      dxl_2_present_veloticy = readVelocity(DXL_2);

      showData(std::string("< DYNAMIXEL 2 >"));
      showData(std::string("present_position  : "), dxl_2_present_position);
      showData(std::string("present_velocity  : "), dxl_2_present_veloticy);
      showData(std::string(" "));
    }

    if (get_id_[index] == SENSOR)
    {
      imu_data   = readIMU(SENSOR);
      temp_data  = readTemp(SENSOR);
      color_data = readColor(SENSOR);
      adc_data   = readADC(SENSOR);

      showData(std::string("< PNP DEV BOARD >"));
      showData(std::string("imu_data[Roll]    : "), imu_data[0]);
      showData(std::string("imu_data[Pitch]   : "), imu_data[1]);
      showData(std::string("imu_data[Yaw]     : "), imu_data[2]);
      showData(std::string(" "));

      showData(std::string("temp_data         : "), temp_data[0]);
      showData(std::string(" "));

      showData(std::string("color_data[RED]   : "), color_data[0]);
      showData(std::string("color_data[GREEN] : "), color_data[1]);
      showData(std::string("color_data[BLUE]  : "), color_data[2]);
      showData(std::string(" "));

      showData(std::string("adc_data[ch 1]    : "), adc_data[0]);
      showData(std::string("adc_data[ch 2]    : "), adc_data[2]);
      showData(std::string(" "));
    }
  }

  ui->pnp_listView->setModel(&logging_model_);

  row_count_ = 0;

}

void MainWindow::showData(const std::string &msg, int64_t value)
{
    if(logging_model_.rowCount() == row_count_)
        logging_model_.insertRows(row_count_, 1);

    std::stringstream logging_model_msg;

    logging_model_msg << msg << value;

    QVariant new_row(QString(logging_model_msg.str().c_str()));
    logging_model_.setData(logging_model_.index(row_count_), new_row);

    row_count_++;
}

void MainWindow::showData(const std::string &msg)
{
    if(logging_model_.rowCount() == row_count_)
        logging_model_.insertRows(row_count_, 1);

    std::stringstream logging_model_msg;

    logging_model_msg << msg;

    QVariant new_row(QString(logging_model_msg.str().c_str()));
    logging_model_.setData(logging_model_.index(row_count_), new_row);

    row_count_++;
}

void MainWindow::log(const std::string &msg, int64_t value)
{
    time_logging_model_.insertRows(time_logging_model_.rowCount(), 1);

    std::stringstream logging_model_msg;

    logging_model_msg << msg << value;

    QVariant new_row(QString(logging_model_msg.str().c_str()));
    time_logging_model_.setData(time_logging_model_.index(time_logging_model_.rowCount()-1), new_row);
}

void MainWindow::log(const std::string &msg)
{
    time_logging_model_.insertRows(time_logging_model_.rowCount(), 1);

    std::stringstream logging_model_msg;

    logging_model_msg << msg;

    QVariant new_row(QString(logging_model_msg.str().c_str()));
    time_logging_model_.setData(time_logging_model_.index(time_logging_model_.rowCount()-1), new_row);
}

void MainWindow::on_connect_pushButton_clicked()
{
  uint8_t error = 0;
  uint8_t id = 0;
  uint16_t model_num = 0;
  uint8_t baud_rate_index = 0;

  tools_cnt_ = 0;
  qtimer_->stop();

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

  get_baud_rate_ = baud_rate_index;

  if (tools_cnt_ != 0)
  {
    QString qstr;
    qstr = QString("<h2>CONNECTION</h2><p> <strong>ID : %1 %2 %3</strong> <br /> Initialization Success</p>").arg(get_id_[0]).arg(get_id_[1]).arg(get_id_[2]);

    QMessageBox::about(this, tr("INFO"), qstr);

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

    connect(qtimer_, SIGNAL(timeout()), this, SLOT(updateData()));
    qtimer_->start(TIMER_MILLIS);
  }
  else
  {
    QMessageBox::about(this, tr("ERROR"),tr("<h2>DYNAMIXEL</h2><p>Initialization Failed!!</p>"));
  }
}

void MainWindow::writeLine(QString qstr)
{
  QString line = qstr;

  QByteArray str;
  str.append(line);

  file_->write(str);
}

void MainWindow::on_single_read_write_button_clicked()
{
  output_info sync_write_info = {false, 0};
  output_info sync_read_info = {false, 0};
  static int index = 0;
  int32_t read_present_position = 0;
  float goal_degree[2] = {90.0, -90.0};
  int32_t send_goal_position = 0;

  QString first_line = QString("SINGLE DYNAMIXEL 4 BYTE ") + QString("BaudRate ") + QString::number(baud_rate_[get_baud_rate_]) + QString(" ");
  writeLine(first_line);

  jointMode(get_id_[0], 200, 50);

  QTime t;
  t.start();

  log(std::string("SINGLE DYNAMIXEL 4 BYTE, BAUD_RATE : "), baud_rate_[get_baud_rate_]);

  while (t.elapsed() < 1 * 1000) // 5 seconds
  {
    send_goal_position = convertRadian2Value(get_id_[0], DEG2RAD(goal_degree[index]));

    sync_write_info = syncWrite(1, &send_goal_position);

    do
    {
      sync_read_info = syncRead(1, ADDR_DYNAMIXEL_PRESENT_POSITION, LEN_DYNAMIXEL_PRESENT_POSITION, &read_present_position);

    }while((abs(send_goal_position - read_present_position) > 5));

    if (index == 0)
      index = 1;
    else
      index = 0;
  }

  log(std::string("WRITE TIME : "), sync_write_info.time);
  log(std::string("READ TIME : "), sync_read_info.time);

  log(std::string(" "));
  ui->log_listView->setModel(&time_logging_model_);

  QString write_data = QString("dynamixel write time ") + QString::number(sync_write_info.time) + QString(" ");
  QString read_data  = QString("dynamixel read time ")  + QString::number(sync_read_info.time)  + QString("\n");

  writeLine(write_data);
  writeLine(read_data);

  torque(get_id_[0], false);
}

void MainWindow::on_multi_read_write_button_clicked()
{
  output_info sync_write_info = {false, 0};
  output_info sync_read_info = {false, 0};
  static int index = 0;
  int32_t read_present_position[2] = {0, 0};
  float goal_degree[2] = {90.0, -90.0};
  int32_t send_goal_position[2] = {0, 0};

  QString first_line = QString("MULTI DYNAMIXEL 4 BYTE ") + QString("BaudRate ") + QString::number(baud_rate_[get_baud_rate_]) + QString(" ");
  writeLine(first_line);

  jointMode(get_id_[0], 200, 50);
  jointMode(get_id_[1], 200, 50);

  QTime t;
  t.start();

  log(std::string("MULTI DYNAMIXEL 4 BYTE, BAUD_RATE : "), baud_rate_[get_baud_rate_]);

  while (t.elapsed() < 1 * 1000) // 5 seconds
  {
    send_goal_position[0] = convertRadian2Value(get_id_[0], DEG2RAD(goal_degree[index]));
    send_goal_position[1] = convertRadian2Value(get_id_[1], DEG2RAD(goal_degree[index]));

    sync_write_info = syncWrite(2, &send_goal_position[0]);

    do
    {
      sync_read_info = syncRead(2, ADDR_DYNAMIXEL_PRESENT_POSITION, LEN_DYNAMIXEL_PRESENT_POSITION, &read_present_position[0]);

    }while((abs(send_goal_position[0] - read_present_position[0]) > 5) && (abs(send_goal_position[1] - read_present_position[1]) > 5));

    if (index == 0)
      index = 1;
    else
      index = 0;
  }

  log(std::string("WRITE TIME : "), sync_write_info.time);
  log(std::string("READ TIME : "), sync_read_info.time);

  log(std::string(" "));
  ui->log_listView->setModel(&time_logging_model_);

  QString write_data = QString("dynamixel write time ") + QString::number(sync_write_info.time) + QString(" ");
  QString read_data  = QString("dynamixel read time ")  + QString::number(sync_read_info.time)  + QString("\n");

  writeLine(write_data);
  writeLine(read_data);

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

int32_t* MainWindow::readIMU(uint8_t id)
{
  static int32_t imu_data[3] = {0, 0, 0};

  readRegister(id, "IMU Roll",  &imu_data[0]);
  readRegister(id, "IMU Pitch", &imu_data[1]);
  readRegister(id, "IMU Yaw",   &imu_data[2]);

  return imu_data;
}

int32_t* MainWindow::readTemp(uint8_t id)
{
  static int32_t temp_data = 0;

  readRegister(id, "TempSensor", &temp_data);

  return &temp_data;
}

int32_t* MainWindow::readColor(uint8_t id)
{
  static int32_t color_data[3] = {0, 0, 0};

  readRegister(id, "ColorSensor Red",       &color_data[0]);
  readRegister(id, "ColorSensor Green",     &color_data[1]);
  readRegister(id, "ColorSensor Blue",      &color_data[2]);

  return color_data;
}

int32_t* MainWindow::readADC(uint8_t id)
{
  static int32_t adc_data[2] = {0, 0};

  readRegister(id, "AdcSensor CH1",            &adc_data[0]);
  readRegister(id, "AdcSensor CH2",            &adc_data[1]);

  return adc_data;
}

int32_t* MainWindow::readTime(uint8_t id)
{
  static int32_t time_data[13] = {0, };

  readRegister(id, "TempSensor Read Time",   &time_data[0]);

  readRegister(id, "ColorSensor Read Time",   &time_data[1]);

  readRegister(id, "AdcSensor CH1 Read Time",   &time_data[2]);
  readRegister(id, "AdcSensor CH2 Read Time",   &time_data[3]);
  readRegister(id, "AdcSensor CH3 Read Time",   &time_data[4]);
  readRegister(id, "AdcSensor CH4 Read Time",   &time_data[5]);
  readRegister(id, "AdcSensor CH5 Read Time",   &time_data[6]);
  readRegister(id, "AdcSensor CH6 Read Time",   &time_data[7]);
  readRegister(id, "AdcSensor CH7 Read Time",   &time_data[8]);

  readRegister(id, "I2C_Read_Speed CH1",   &time_data[9]);
  readRegister(id, "I2C_Write_Speed CH1",  &time_data[10]);
  readRegister(id, "I2C_Read_Speed CH2",   &time_data[11]);
  readRegister(id, "I2C_Write_Speed CH2",  &time_data[12]);

  return time_data;
}

void MainWindow::on_close_pushButton_clicked()
{
  portHandler_->closePort();
  file_->close();
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
  get_baud_rate_ = 0;

  for (int index = 0; index < tools_cnt_; index++)
  {
    if (get_id_[index] < 100)
      torque(get_id_[index], false);
    writeRegister(get_id_[index], "Baud Rate", 1);
  }

 if (setBaudrate(baud) == false)
 {
   QString qstr;
   qstr = QString("<h2>CONNECTION</h2><p> Failed to set baudrate</p>");

   QMessageBox::about(this, tr("INFO"), qstr);
 }

 ui->connect_pushButton->setEnabled(true);
}

void MainWindow::on_radioButton_115200_clicked()
{
  int32_t baud = 115200;
  get_baud_rate_ = 1;

  for (int index = 0; index < tools_cnt_; index++)
  {
    if (get_id_[index] < 100)
      torque(get_id_[index], false);
    writeRegister(get_id_[index], "Baud Rate", 2);
  }

  if (setBaudrate(baud) == false)
  {
    QString qstr;
    qstr = QString("<h2>CONNECTION</h2><p> Failed to set baudrate</p>");

    QMessageBox::about(this, tr("INFO"), qstr);
  }

  ui->connect_pushButton->setEnabled(true);
}

void MainWindow::on_radioButton_1000000_clicked()
{
  int32_t baud = 1000000;
  get_baud_rate_ = 2;

  for (int index = 0; index < tools_cnt_; index++)
  {
    if (get_id_[index] < 100)
      torque(get_id_[index], false);
    writeRegister(get_id_[index], "Baud Rate", 3);
  }

  if (setBaudrate(baud) == false)
  {
    QString qstr;
    qstr = QString("<h2>CONNECTION</h2><p> Failed to set baudrate</p>");

    QMessageBox::about(this, tr("INFO"), qstr);
  }

  ui->connect_pushButton->setEnabled(true);
}

void MainWindow::on_radioButton_2000000_clicked()
{
  int32_t baud = 2000000;
  get_baud_rate_ = 3;

  for (int index = 0; index < tools_cnt_; index++)
  {
    if (get_id_[index] < 100)
      torque(get_id_[index], false);
    writeRegister(get_id_[index], "Baud Rate", 4);
  }

  if (setBaudrate(baud) == false)
  {
    QString qstr;
    qstr = QString("<h2>CONNECTION</h2><p> Failed to set baudrate</p>");

    QMessageBox::about(this, tr("INFO"), qstr);
  }

  ui->connect_pushButton->setEnabled(true);
}

void MainWindow::on_radioButton_3000000_clicked()
{
  int32_t baud = 3000000;
  get_baud_rate_ = 4;

  for (int index = 0; index < tools_cnt_; index++)
  {
    if (get_id_[index] < 100)
      torque(get_id_[index], false);
    writeRegister(get_id_[index], "Baud Rate", 5);
  }

  if (setBaudrate(baud) == false)
  {
    QString qstr;
    qstr = QString("<h2>CONNECTION</h2><p> Failed to set baudrate</p>");

    QMessageBox::about(this, tr("INFO"), qstr);
  }

  ui->connect_pushButton->setEnabled(true);
}

uint32_t MainWindow::micros()
{
  struct timeval ts;

  gettimeofday(&ts, NULL);
  return ( ts.tv_sec * 1000 + ts.tv_usec );
}

void MainWindow::on_all_tools_read_button_clicked()
{
  output_info sync_write_info = {false, 0};
  output_info sync_read_info = {false, 0};
  static int index = 0;
  int32_t read_present_position[3] = {0, 0, 0};
  float goal_degree[2] = {90.0, -90.0};
  int32_t send_goal_position[2] = {0, 0};
  int32_t* time_data;

  QString first_line = QString("ALL TOOLS 4 BYTE ") + QString("BaudRate ") + QString::number(baud_rate_[get_baud_rate_]) + QString(" ");
  writeLine(first_line);

  jointMode(get_id_[0], 200, 50);
  jointMode(get_id_[1], 200, 50);

  QTime t;
  t.start();

  log(std::string("ALL TOOLS 4 BYTE, BAUD_RATE : "), baud_rate_[get_baud_rate_]);

  while (t.elapsed() < 1 * 1000) // 1 seconds
  {
    send_goal_position[0] = convertRadian2Value(get_id_[0], DEG2RAD(goal_degree[index]));
    send_goal_position[1] = convertRadian2Value(get_id_[1], DEG2RAD(goal_degree[index]));

    sync_write_info = syncWrite(2, &send_goal_position[0]);

    do
    {
      sync_read_info = syncRead(3, ADDR_DYNAMIXEL_PRESENT_POSITION, LEN_DYNAMIXEL_PRESENT_POSITION, &read_present_position[0]);

    }while((abs(send_goal_position[0] - read_present_position[0]) > 5) && (abs(send_goal_position[1] - read_present_position[1]) > 5));

    if (index == 0)
      index = 1;
    else
      index = 0;
  }

  log(std::string("WRITE TIME : "), sync_write_info.time);
  log(std::string("READ TIME : "), sync_read_info.time);

  time_data = readTime(get_id_[2]);

  log(std::string("TempSensor Read Time    : "), time_data[0]);
  log(std::string("ColorSensor Read Time   : "), time_data[1]);
  log(std::string("AdcSensor CH1 Read Time : "), time_data[2]);
  log(std::string("AdcSensor CH2 Read Time : "), time_data[3]);
  log(std::string("AdcSensor CH3 Read Time : "), time_data[4]);
  log(std::string("AdcSensor CH4 Read Time : "), time_data[5]);
  log(std::string("AdcSensor CH5 Read Time : "), time_data[6]);
  log(std::string("AdcSensor CH6 Read Time : "), time_data[7]);
  log(std::string("AdcSensor CH7 Read Time : "), time_data[8]);
  log(std::string("I2C_Read_Speed CH1      : "), time_data[9]);
  log(std::string("I2C_Write_Speed CH1     : "), time_data[10]);
  log(std::string("I2C_Read_Speed CH2      : "), time_data[11]);
  log(std::string("I2C_Write_Speed CH2     : "), time_data[12]);

  log(std::string(" "));
  ui->log_listView->setModel(&time_logging_model_);

  QString write_data = QString("dynamixel write time ") + QString::number(sync_write_info.time) + QString(" ");
  QString read_data  = QString("dynamixel read time ")  + QString::number(sync_read_info.time)  + QString(" ");

  QString temp_read_data = QString("temp read time ") + QString::number(time_data[0]) + QString(" ");
  QString color_read_data  = QString("color read time ")  + QString::number(time_data[1])  + QString(" ");
  QString adc_ch1_read_data = QString("adc ch1 read time ") + QString::number(time_data[2]) + QString(" ");
  QString adc_ch2_read_data  = QString("adc ch2 read time ")  + QString::number(time_data[3])  + QString(" ");
  QString adc_ch3_read_data = QString("adc ch3 read time ") + QString::number(time_data[4]) + QString(" ");
  QString adc_ch4_read_data  = QString("adc ch4 read time ")  + QString::number(time_data[5])  + QString(" ");
  QString adc_ch5_read_data = QString("adc ch5 read time ") + QString::number(time_data[6]) + QString(" ");
  QString adc_ch6_read_data  = QString("adc ch6 read time ")  + QString::number(time_data[7])  + QString(" ");
  QString adc_ch7_read_data = QString("adc ch7 read time ") + QString::number(time_data[8]) + QString(" ");
  QString i2c_ch1_read_data  = QString("i2c ch1 read speed ")  + QString::number(time_data[9])  + QString(" ");
  QString i2c_ch1_write_data = QString("i2c ch1 write speed ") + QString::number(time_data[10]) + QString(" ");
  QString i2c_ch2_read_data  = QString("i2c ch2 read speed ")  + QString::number(time_data[11])  + QString(" ");
  QString i2c_ch2_write_data = QString("i2c ch2 write speed ") + QString::number(time_data[12]) + QString("\n");

  writeLine(write_data);
  writeLine(read_data);

  writeLine(temp_read_data);
  writeLine(color_read_data);

  writeLine(adc_ch1_read_data);
  writeLine(adc_ch2_read_data);
  writeLine(adc_ch3_read_data);
  writeLine(adc_ch4_read_data);
  writeLine(adc_ch5_read_data);
  writeLine(adc_ch6_read_data);
  writeLine(adc_ch7_read_data);

  writeLine(i2c_ch1_read_data);
  writeLine(i2c_ch1_write_data);
  writeLine(i2c_ch2_read_data);
  writeLine(i2c_ch2_write_data);

  torque(get_id_[0], false);
  torque(get_id_[1], false);
}
