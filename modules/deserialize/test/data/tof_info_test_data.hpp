#include <array>

namespace ifm3d
{
  namespace tof_info_v3
  {
    constexpr uint32_t version = 3;
    constexpr float distance_resolution = 0.00015259;
    constexpr float amplitude_resolution = 2.32989e-08;
    constexpr std::array<float, 3> amp_normalization_factors = {
      0.0500309,
      0.0025,
      0.000200025,
    };
    constexpr std::array<float, 6> extrincsic_optic_to_user =
      {0, 0, 0.00841006, -0.0204563, 0.0181109, -0.00622652};
    constexpr uint32_t intrinsic_calib_model_id = {0};
    constexpr std::array<float, 32> intrinsic_calib_model_param = {
      128.5714264,
      128.5714264,
      112.7824249,
      83.43323517,
      0,
      0.5029289722,
      -0.4033640027,
      0,
      0,
      0.6367549896,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
    };
    constexpr uint32_t inverse_intrinsic_calib_model_id = {1};
    constexpr std::array<float, 32> inverse_intrinsic_calib_model_param = {
      128.5714264,
      128.5714264,
      112.7824249,
      83.43323517,
      0,
      -0.2719089985,
      0.05658800155,
      0,
      0,
      -0.004511999898,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
    };
    constexpr std::array<uint64_t, 3> exposure_timestamps_ns = {
      1581587830148502150,
      1581587830144571155,
      1581587830131172393,
    };
    constexpr std::array<uint32_t, 3> exposure_times_s = {
      933735213,
      970045206,
      1000591837,
    };

    constexpr float illu_temperature = 58.336933135986328;

    constexpr std::array<char, 32> mode = {
      's',  't',  'a',  'n',  'd',  'a',  'r',  'd',  '_',  'r',  'a',
      'n',  'g',  'e',  '4',  'm',  '\0', '\0', '\0', '\0', '\0', '\0',
      '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    };
    constexpr std::array<char, 32> imager = {
      'I',  'R',  'S',  '2',  '3',  '8',  '1',  'C',  '\0', '\0', '\0',
      '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
      '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    };

  }
}