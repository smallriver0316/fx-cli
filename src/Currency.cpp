#include <algorithm>
#include <array>

#include "fx/Currency.hpp"

const std::array<std::pair<std::string, CurrencyPair>, 24> currency_pair_map = {{{"USDJPY", CurrencyPair::USDJPY},
                                                                                 {"EURJPY", CurrencyPair::EURJPY},
                                                                                 {"EURUSD", CurrencyPair::EURUSD},
                                                                                 {"AUDCHF", CurrencyPair::AUDCHF},
                                                                                 {"AUDJPY", CurrencyPair::AUDJPY},
                                                                                 {"AUDNZD", CurrencyPair::AUDNZD},
                                                                                 {"AUDUSD", CurrencyPair::AUDUSD},
                                                                                 {"CADJPY", CurrencyPair::CADJPY},
                                                                                 {"CHFJPY", CurrencyPair::CHFJPY},
                                                                                 {"EURAUD", CurrencyPair::EURAUD},
                                                                                 {"EURCAD", CurrencyPair::EURCAD},
                                                                                 {"EURCHF", CurrencyPair::EURCHF},
                                                                                 {"EURGBP", CurrencyPair::EURGBP},
                                                                                 {"EURNZD", CurrencyPair::EURNZD},
                                                                                 {"GBPAUD", CurrencyPair::GBPAUD},
                                                                                 {"GBPCHF", CurrencyPair::GBPCHF},
                                                                                 {"GBPJPY", CurrencyPair::GBPJPY},
                                                                                 {"GBPNZD", CurrencyPair::GBPNZD},
                                                                                 {"GBPUSD", CurrencyPair::GBPUSD},
                                                                                 {"NZDJPY", CurrencyPair::NZDJPY},
                                                                                 {"NZDUSD", CurrencyPair::NZDUSD},
                                                                                 {"USDCAD", CurrencyPair::USDCAD},
                                                                                 {"USDCHF", CurrencyPair::USDCHF},
                                                                                 {"ZARJPY", CurrencyPair::ZARJPY}}};

const std::array<std::pair<std::string, CryptoCurrencyPair>, 13> crypto_pair_map = {{{"BTCJPY", CryptoCurrencyPair::BTCJPY},
                                                                                     {"BTCUSD", CryptoCurrencyPair::BTCUSD},
                                                                                     {"ETHJPY", CryptoCurrencyPair::ETHJPY},
                                                                                     {"ETHUSD", CryptoCurrencyPair::ETHUSD},
                                                                                     {"XRPJPY", CryptoCurrencyPair::XRPJPY},
                                                                                     {"XRPUSD", CryptoCurrencyPair::XRPUSD},
                                                                                     {"LTCJPY", CryptoCurrencyPair::LTCJPY},
                                                                                     {"LTCUSD", CryptoCurrencyPair::LTCUSD},
                                                                                     {"XEMJPY", CryptoCurrencyPair::XEMJPY},
                                                                                     {"XEMUSD", CryptoCurrencyPair::XEMUSD},
                                                                                     {"ADAUSD", CryptoCurrencyPair::ADAUSD},
                                                                                     {"BNBBTC", CryptoCurrencyPair::BNBBTC},
                                                                                     {"BNBUSDT", CryptoCurrencyPair::BNBUSDT}}};

std::array<std::pair<std::string, CurrencyPair>, 24>::const_iterator getCurrencyPair(std::string key)
{
  auto it = std::find_if(currency_pair_map.begin(), currency_pair_map.end(), [&key](const auto &pair)
                         { return pair.first == key; });
  return it;
}

std::array<std::pair<std::string, CryptoCurrencyPair>, 13>::const_iterator getCryptoCurrencyPair(std::string key)
{
  auto it = std::find_if(crypto_pair_map.begin(), crypto_pair_map.end(), [&key](const auto &pair)
                         { return pair.first == key; });
  return it;
}

bool Currency::isForwardCurrencyPair(std::string prev, std::string next)
{
  auto pair = prev + next;
  return pair.length() == 6 && getCurrencyPair(pair) != currency_pair_map.end();
}

bool Currency::isReverseCurrencyPair(std::string prev, std::string next)
{
  auto pair = next + prev;
  return pair.length() == 6 && getCurrencyPair(pair) != currency_pair_map.end();
}

bool Currency::isForwardCryptoPair(std::string prev, std::string next)
{
  auto pair = prev + next;
  return getCryptoCurrencyPair(pair) != crypto_pair_map.end();
}

bool Currency::isReverseCryptoPair(std::string prev, std::string next)
{
  auto pair = next + prev;
  return getCryptoCurrencyPair(pair) != crypto_pair_map.end();
}

std::string Currency::toPairString(std::string prev, std::string next)
{
  std::transform(prev.begin(), prev.end(), prev.begin(), ::tolower);
  std::transform(next.begin(), next.end(), next.begin(), ::tolower);

  return prev + "-" + next;
}
