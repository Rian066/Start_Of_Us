# import yfinance as yf
# import subprocess
# import time
# from datetime import datetime
# import pandas as pd
# import numpy as np
# import logging

# # Set up logging
# logging.basicConfig(
#     filename="forex_bot.log", level=logging.INFO, format="%(asctime)s - %(message)s"
# )

# # Constants
# RSI_OVERBOUGHT = 70
# RSI_OVERSOLD = 30
# TIME_INTERVAL = "1m"
# FOREX_PAIR = "AUDCAD=X"  # Example pair, replace as needed
# EXPIRATION_TIME = 2  # Expiration time in minutes


# def fetch_forex_data(pair: str, interval: str, period: str = "1d"):
#     """Fetch forex data from Yahoo Finance."""
#     try:
#         data = yf.download(pair, interval=interval, period=period, progress=False)
#         if not data.empty:
#             return data
#         else:
#             logging.error("Error: Data is empty.")
#             return None
#     except Exception as e:
#         logging.error(f"Error fetching data: {e}")
#         return None


# def calculate_rsi(data: pd.Series, period: int = 5):
#     """Calculate the Relative Strength Index (RSI)."""
#     delta = data.diff(1)
#     gain = (delta.where(delta > 0, 0)).rolling(window=period).mean()
#     loss = (-delta.where(delta < 0, 0)).rolling(window=period).mean()
#     rs = gain / loss
#     rsi = 100 - (100 / (1 + rs))
#     return rsi


# def calculate_macd(data: pd.Series, short_window=6, long_window=13, signal_window=5):
#     """Calculate MACD and Signal Line."""
#     short_ema = data.ewm(span=short_window, adjust=False).mean()
#     long_ema = data.ewm(span=long_window, adjust=False).mean()
#     macd = short_ema - long_ema
#     signal = macd.ewm(span=signal_window, adjust=False).mean()
#     return macd, signal


# def calculate_bollinger_bands(data: pd.Series, window=10):
#     """Calculate Bollinger Bands."""
#     sma = data.rolling(window=window).mean()
#     stddev = data.rolling(window=window).std()
#     upper_band = sma + (2 * stddev)
#     lower_band = sma - (2 * stddev)
#     return upper_band, lower_band


# def calculate_support_resistance(data: pd.DataFrame, window=5):
#     """
#     Calculate support and resistance levels using rolling max/min.
#     """
#     data["Resistance"] = data["High"].rolling(window=window).max()
#     data["Support"] = data["Low"].rolling(window=window).min()
#     return data


# def analyze_forex_data(data):
#     """Analyze forex data and generate trading signals."""
#     # Calculate indicators
#     data["RSI"] = calculate_rsi(data["Close"])
#     data["MACD"], data["MACD_Signal"] = calculate_macd(data["Close"])
#     data["Upper_Band"], data["Lower_Band"] = calculate_bollinger_bands(data["Close"])
#     data = calculate_support_resistance(data)

#     # Get latest data points
#     latest = data.iloc[-1]
#     close_price = latest["Close"]
#     rsi = latest["RSI"]
#     macd = latest["MACD"]
#     macd_signal = latest["MACD_Signal"]
#     upper_band = latest["Upper_Band"]
#     lower_band = latest["Lower_Band"]
#     support = latest["Support"]
#     resistance = latest["Resistance"]

#     # Signal logic
#     if pd.isna(rsi) or pd.isna(macd) or pd.isna(macd_signal):
#         return "HOLD"

#     # Enhanced signal logic for short-term trades
#     if close_price <= support and rsi < RSI_OVERSOLD and macd > macd_signal:
#         return "BUY"
#     elif close_price >= resistance and rsi > RSI_OVERBOUGHT and macd < macd_signal:
#         return "SELL"
#     elif close_price > upper_band and rsi > RSI_OVERBOUGHT:
#         return "SELL"
#     elif close_price < lower_band and rsi < RSI_OVERSOLD:
#         return "BUY"

#     return "HOLD"


# def main():
#     print(
#         f"Starting binary forex bot for {FOREX_PAIR} with {EXPIRATION_TIME}-minute expiration..."
#     )
#     previous_signal = ""
#     while True:
#         try:
#             # Fetch data
#             data = fetch_forex_data(FOREX_PAIR, TIME_INTERVAL)
#             if data is None or data.empty:
#                 time.sleep(60)  # Fetch every 30 seconds
#                 continue

#             # Analyze data
#             signal = analyze_forex_data(data)
#             if signal != previous_signal:
#                 print(f"[{datetime.now()}] Signal: {signal}")
#                 logging.info(f"Signal: {signal}")

#                 # Play sound on signal change (adapt for your OS)
#                 if signal in ["BUY", "SELL"]:
#                     subprocess.run(
#                         ["afplay", "Money.mp3"]
#                     )  # Replace with appropriate sound command

#             previous_signal = signal
#             time.sleep(60)  # Shorten delay to increase reaction speed
#         except Exception as e:
#             logging.error(f"Error in main loop: {e}")
#             time.sleep(60)


# if __name__ == "__main__":
#     main()


#######################################
import yfinance as yf
import subprocess
import time
import threading
from datetime import datetime
import pandas as pd
import logging

# Pick the market
forex = 0
stocks = 1
market = forex
# Forex pair to analyze (e.g., EUR/USD)
if market == 0:
    Pair_Input = input("Pair: ")
    FOREX_PAIR = Pair_Input + "=X"  # Format for Yahoo Finance forex data
elif market == 1:
    FOREX_PAIR = input("Pair: ")

# Time interval for data (e.g., 1m, 5m, 15m)
TIME_INTERVAL = "1m"

# RSI thresholds
RSI_OVERBOUGHT = 69
RSI_OVERSOLD = 31

Above_Band = None

PREVIOUS_SIGNAL = ""

# Set up logging
logging.basicConfig(
    filename="forex_bot.log", level=logging.INFO, format="%(asctime)s - %(message)s"
)


def fetch_forex_data(pair: str, interval: str):
    """
    Fetch forex data from Yahoo Finance.
    """
    try:
        logging.info(f"Fetching data for {pair} at {interval} interval...")
        data = yf.download(pair, interval=interval, period="5d", progress=False)
        if not data.empty:
            logging.info(f"Successfully fetched data for {pair}.")
            return data
        else:
            logging.error("Error: Data is empty.")
            return None
    except Exception as e:
        logging.error(f"Error fetching data from Yahoo Finance: {e}")
        return None


def calculate_rsi(data: pd.Series, period: int = 10):
    """
    Calculate the Relative Strength Index (RSI).
    """
    delta = data.diff(1)
    gain = (delta.where(delta > 0, 0)).rolling(window=period).mean()
    loss = (-delta.where(delta < 0, 0)).rolling(window=period).mean()
    rs = gain / loss
    rsi = 100 - (100 / (1 + rs))
    return rsi


def calculate_rate_of_change(data: pd.Series, period):
    """
    Calculate the rate of change (ROC) over a given period.
    """
    ROC = float((data.iloc[-1].values[0] - data.iloc[-(period + 1)].values[0]) / period)
    return ROC


def calculate_macd(
    data: pd.Series,
    short_window: int = 12,
    long_window: int = 26,
    signal_window: int = 9,
):
    """
    Calculate MACD and MACD signal line.
    """
    short_ema = data.ewm(span=short_window, adjust=False).mean()
    long_ema = data.ewm(span=long_window, adjust=False).mean()
    macd = short_ema - long_ema
    signal = macd.ewm(span=signal_window, adjust=False).mean()
    return macd, signal


def calculate_bollinger_bands(data: pd.Series, window: int = 20):
    """
    Calculate Bollinger Bands.
    """
    sma = data.rolling(window=window).mean()
    stddev = data.rolling(window=window).std()
    upper_band = sma + (stddev)
    lower_band = sma - (stddev)
    return upper_band, lower_band


def check_bollinger_bands(lower_band, upper_band, close):
    global Above_Band
    if close > upper_band:
        Above_Band = True
    elif close < lower_band:
        Above_Band = False
    else:
        Above_Band = None
    time.sleep(120)


def analyze_forex_data(data):
    """
    Analyze forex data and give buy/sell signals based on indicators.
    """
    global Above_Band

    df = data.copy()
    df["RSI"] = calculate_rsi(df["Close"])
    df["MACD"], df["MACD_Signal"] = calculate_macd(df["Close"])
    df["Upper_Band"], df["Lower_Band"] = calculate_bollinger_bands(df["Close"])
    df["Volatility"] = df["Close"].pct_change().rolling(window=14).std()
    df["ROC_1min"] = calculate_rate_of_change(df["Close"], 1)
    df["ROC_2min"] = calculate_rate_of_change(df["Close"], 2)
    df["ROC_5min"] = calculate_rate_of_change(df["Close"], 5)

    if len(df) < 15:
        logging.warning("Not enough data for analysis. Waiting for more data...")
        return "HOLD"

    # Extract the latest values of indicators
    latest_rsi = df["RSI"].iloc[-1]
    latest_macd = df["MACD"].iloc[-1]
    latest_signal_line = df["MACD_Signal"].iloc[-1]
    latest_upper_band = df["Upper_Band"].iloc[-1]
    latest_lower_band = df["Lower_Band"].iloc[-1]
    volatility = df["Volatility"].iloc[-1]
    latest_close = df["Close"].iloc[-1].values[0]
    latest_ROC_1min = df["ROC_1min"].iloc[-1]
    latest_ROC_2min = df["ROC_2min"].iloc[-1]
    latest_ROC_5min = df["ROC_5min"].iloc[-1]

    # Check if Above_Band
    threading.Thread(
        target=check_bollinger_bands,
        args=(latest_lower_band, latest_upper_band, latest_close),
        daemon=True,
    ).start()

    if pd.isna(volatility):
        volatility = 0

    # Adjust RSI thresholds dynamically based on volatility
    adjusted_rsi_overbought = (
        RSI_OVERBOUGHT - 5 if volatility > 0.0005 else RSI_OVERBOUGHT
    )
    adjusted_rsi_oversold = RSI_OVERSOLD + 5 if volatility > 0.0005 else RSI_OVERSOLD

    print(
        f"""
        \nClose = {latest_close},
        RSI = {latest_rsi}
        Overbought = {adjusted_rsi_overbought},
        Oversold = {adjusted_rsi_oversold},
        MACD = {latest_macd},
        MACD_Signal = {latest_signal_line},
        Lower_Band = {latest_lower_band},
        Upper_Band = {latest_upper_band},
        Above_Band = {Above_Band},
        Volatility = {volatility},
        1_min = {latest_ROC_1min}
        2_min = {latest_ROC_2min}
        5_min = {latest_ROC_5min}
        """
    )

    # logging.info(
    #     f"{latest_macd}, \n{latest_signal_line}, \n{latest_upper_band}, \n{latest_lower_band}, \n{latest_ROC_2min}, \n{latest_ROC_5min}, \n{adjusted_rsi_overbought}, \n{adjusted_rsi_oversold}, "
    # )
    # Signal logic
    if latest_rsi < adjusted_rsi_oversold and (
        latest_ROC_5min > 0 or latest_ROC_1min > 0
    ):
        print("line 182")
        return "BUY"
    elif latest_rsi > adjusted_rsi_overbought and (
        latest_ROC_5min < 0 or latest_ROC_1min < 0
    ):
        print("line 185")
        return "SELL"
    elif Above_Band == True and latest_ROC_1min < 0:
        print("line 188")
        return "SELL"
    elif Above_Band == False and latest_ROC_1min > 0:
        print("line 191")
        return "BUY"
    elif (
        latest_macd > latest_signal_line and latest_ROC_1min > 0 and latest_ROC_2min > 0
    ):
        print("line 195")
        return "BUY"
    elif (
        latest_macd < latest_signal_line and latest_ROC_1min < 0 and latest_ROC_2min < 0
    ):
        print("line 202")
        return "SELL"

    return "HOLD"


def main():
    global PREVIOUS_SIGNAL
    print(f"Starting binary forex bot for {FOREX_PAIR}...")
    while True:
        try:
            # Fetch data
            data = fetch_forex_data(FOREX_PAIR, TIME_INTERVAL)
            if data is None:
                logging.error("No data received. Retrying...")
                time.sleep(90)
                continue

            # Analyze data
            signal = analyze_forex_data(data)
            if signal != PREVIOUS_SIGNAL:
                logging.info(f"[{datetime.now()}] Signal for {FOREX_PAIR}: {signal}")
                print(f"[{datetime.now()}] Signal for {FOREX_PAIR}: {signal}\n-------")

                # Play sound based on signal
                if signal == "BUY" or signal == "SELL":
                    subprocess.run(
                        ["afplay", "Money.mp3"]
                    )  # Replace with sound player for your OS

            PREVIOUS_SIGNAL = signal
            time.sleep(90)
        except Exception as e:
            logging.error(f"An error occurred: {e}")
            time.sleep(90)


if __name__ == "__main__":
    main()
