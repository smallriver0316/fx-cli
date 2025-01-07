#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "CLI/CLI.hpp"

#include "fx/Formatter.hpp"
#include "fx/FxInterface.hpp"

int main(int argc, char **argv)
{
  CLI::App app{"Exchange a given value in currency with specified format"};
  argv = app.ensure_utf8(argv);

  // add version output
  app.set_version_flag("-v,--version", "1.0");

  // add format option
  std::string format;
  app.add_option<std::string>(
      "-f, --format",
      format,
      "Format to use for output, such as ENG, default is the style formatted with thousand separator");

  // add input-currency option
  std::string input_currency;
  app.add_option<std::string>(
      "-i, --input-currency",
      input_currency,
      "Input currency, such as USD, EUR, JPY, and so on");

  // add output-currency option
  std::string output_currency;
  app.add_option<std::string>(
      "-o, --output-currency",
      output_currency,
      "Output currency, such as USD, EUR, JPY, and so on");

  std::string input_value;
  app.add_option<std::string>("input_value", input_value, "Input value")->required();

  CLI11_PARSE(app, argc, argv);

  try
  {
    // create Fx instance
    auto fx = std::make_shared<Fx>(input_value);
    auto fx_interface = FxInterface(fx, input_currency, output_currency);

    // print input value
    std::cout << "YOUR INPUT: " << Formatter::to1000sSepAsIs(fx_interface.getOriginalNumString());
    if (!fx_interface.getInputCurrency().empty())
    {
      std::cout << " " << fx_interface.getInputCurrency();
    }
    std::cout << std::endl;

    // select formatter
    std::string (*format_func)(std::string) = nullptr;
    if (format == "ENG")
    {
      format_func = &Formatter::toEnglish;
    }
    else if (format == "DEU" || format == "GER")
    {
      format_func = &Formatter::toGerman;
    }
    else if (format == "SPA")
    {
      format_func = &Formatter::toSpanish;
    }
    else if (format == "FRA")
    {
      format_func = &Formatter::toFrench;
    }
    else if (format == "JPN")
    {
      format_func = &Formatter::toJapanese;
    }
    else
    {
      format_func = &Formatter::to1000sSep;
    }

    // print output result
    auto result = fx_interface.exchange(format_func);
    if (result.empty())
    {
      // something wrong happen
      return 1;
    }

    std::cout << "----------> " << result;

    if (!fx_interface.getOutputCurrency().empty())
    {
      std::cout << " " << fx_interface.getOutputCurrency();
    }
    std::cout << std::endl;
  }
  catch (const ConversionException &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
