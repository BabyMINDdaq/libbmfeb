#ifndef UFE_CONFIGFRAME_H
#define UFE_CONFIGFRAME_H 1

#include <string>
#include <vector>
#include <json/json.h>

struct HardwareVId {
  unsigned int Id_;
  std::string ShortName_;
  std::string FriendlyName_;

  void operator << (const Json::Value &fv_json);
};

struct FirmwareVId {
  unsigned int MajorId_;
  unsigned int MinorId_;
  std::string ShortName_;
  std::string FriendlyName_;

  void operator << (const Json::Value &fv_json);
};

struct MemoryLayout {
  MemoryLayout()
  : Index_(0), Increment_(-1), MsbFirst_(false), Absolute_(false) {}
  unsigned int Index_;
  int Increment_;
  bool MsbFirst_;
  bool Absolute_;
  std::vector<unsigned int> AbsoluteIndexes_;

  void operator << (const Json::Value &v_json);
};

struct Variable {
  std::string Name_;
  std::string Type_;
  int Default_;
  int Min_;
  int Max_;
  int BitSize_;
  MemoryLayout MemoryLayout_;

  void operator << (const Json::Value &v_json);
};

struct Parameters {
  std::vector<Variable> Variables_;
};

struct Board {
  Parameters DirectParameters_;
  Parameters DataReadoutParameters_;
  Parameters StatusParameters_;
};


class UFEConfigFrame {
public:
  UFEConfigFrame() {};
  UFEConfigFrame(Json::Value c);

  virtual ~UFEConfigFrame() {}

  void load(Json::Value c);

private:

  void get_board_config(const Json::Value &c);
  void get_ASICS_config(const Json::Value &c);
  void get_FPGA_config(const Json::Value &c);

  std::string Name_;
  double Version_;
  int DeviceMemorySize_;
  double MinFpgaVersion_;
  std::vector<HardwareVId> HardwareVIds_;
  std::vector<FirmwareVId> FirmwareVIds_;
  Board Board_;
};

#endif
