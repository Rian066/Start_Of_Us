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
RSI_OVERBOUGHT = 65
RSI_OVERSOLD = 35

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


def calculate_rsi(data: pd.Series, period: int = 25):
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
    time.sleep(200)


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
    if latest_rsi < adjusted_rsi_oversold and latest_ROC_1min > 0:
        print("line 179")
        return "BUY"
    elif (
        latest_macd > latest_signal_line and latest_ROC_1min > 0 and latest_ROC_2min > 0
    ):
        print("line 183")
        return "BUY"
    # elif latest_ROC_1min > 0:
    #     print("line 187")
    #     return "BUY"
    elif latest_rsi > adjusted_rsi_overbought and latest_ROC_1min < 0:
        print("line 190")
        return "SELL"
    elif Above_Band == True and latest_ROC_2min < 0:
        print("line 193")
        return "SELL"
    elif Above_Band == False and latest_ROC_2min > 0:
        print("line 196")
        return "BUY"
    # elif latest_ROC_1min < 0:
    #     print("line 199")
    #     return "SELL"
    elif (
        latest_macd < latest_signal_line and latest_ROC_1min < 0 and latest_ROC_2min < 0
    ):
        print("line 203")
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
                time.sleep(120)
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
            time.sleep(120)
        except Exception as e:
            logging.error(f"An error occurred: {e}")
            time.sleep(120)


if __name__ == "__main__":
    main()


##########################################################

# import yfinance as yf
# import subprocess
# import time
# from datetime import datetime
# import pandas as pd
# import logging

# # Forex pair to analyze (e.g., EUR/USD)
# Pair_Input = input("Pair:")
# FOREX_PAIR = Pair_Input + "=X"  # Format for Yahoo Finance forex data

# # Time interval for data (e.g., 1m, 5m, 15m)
# TIME_INTERVAL = "1m"

# # RSI thresholds
# RSI_OVERBOUGHT = 65
# RSI_OVERSOLD = 35

# PREVIOUS_SIGNAL = ""

# # Set up logging
# logging.basicConfig(
#     filename="forex_bot.log", level=logging.INFO, format="%(asctime)s - %(message)s"
# )


# def fetch_forex_data(pair: str, interval: str):
#     """
#     Fetch forex data from Yahoo Finance.
#     """
#     try:
#         # Fetching data for the last 5 days to have more context
#         data = yf.download(pair, interval=interval, period="5d", progress=False)
#         if not data.empty:
#             return data
#         else:
#             logging.error("Error: Data is empty.")
#             return None
#     except Exception as e:
#         logging.error(f"Error fetching data from Yahoo Finance: {e}")
#         return None


# def analyze_forex_data(data):
#     """
#     Analyze forex data and give buy/sell signals based on RSI and rate of change.
#     """
#     df = data.copy()  # Work with the fetched data directly
#     df["RSI"] = calculate_rsi(df["Close"])
#     latest_rsi = df["RSI"].iloc[-1]

#     # Calculate ROC for 2 minute, 5 minutes, 10 minutes, and 15 minutes
#     df["ROC_2min"] = calculate_rate_of_change(df["Close"], period=2)
#     df["ROC_5min"] = calculate_rate_of_change(df["Close"], period=5)
#     df["ROC_10min"] = calculate_rate_of_change(df["Close"], period=10)
#     # df["ROC_15min"] = calculate_rate_of_change(df["Close"], period=15)

#     if len(df) < 15:  # Ensure there are enough rows for RSI and ROC calculation
#         logging.warning(
#             "Not enough data to calculate RSI or rate of change. Waiting for more data..."
#         )
#         return "HOLD"

#     latest_close = df["Close"].iloc[-1]
#     latest_ROC_2min = df["ROC_2min"].iloc[-1]
#     latest_ROC_5min = df["ROC_5min"].iloc[-1]
#     latest_ROC_10min = df["ROC_10min"].iloc[-1]
#     # latest_ROC_15min = df["ROC_15min"].iloc[-1]

#     # Debugging logs
#     logging.info(
#         f"Close={latest_close}, RSI={latest_rsi}, ROC_2min={latest_ROC_2min}, ROC_5min={latest_ROC_5min}, "
#     )
#     print(
#         f"""
#         Close={latest_close},
#         RSI={latest_rsi},
#         ROC_2min={latest_ROC_2min},{FOREX_PAIR} {df["Close"].iloc[-2]},
#         ROC_5min={latest_ROC_5min},{FOREX_PAIR} {df["Close"].iloc[-5]},
#         ROC_10min={latest_ROC_10min},{FOREX_PAIR} {df["Close"].iloc[-10]}
#         """
#     )

#     # Signal logic
#     if latest_rsi < RSI_OVERSOLD:
#         return "HOLD"
#     elif latest_rsi > RSI_OVERBOUGHT:
#         return "HOLD"
#     elif RSI_OVERSOLD < latest_rsi < RSI_OVERBOUGHT:  # RSI between thresholds
#         if latest_ROC_2min > 0 and latest_ROC_5min > 0 and latest_ROC_10min > 0:
#             return "BUY"
#         elif latest_ROC_2min < 0 and latest_ROC_5min < 0 and latest_ROC_10min < 0:
#             return "SELL"
#     return "HOLD"  # Default to HOLD if none of the above conditions are met


# def calculate_rsi(data: pd.Series, period: int = 25):
#     """
#     Calculate the Relative Strength Index (RSI).
#     """
#     delta = data.diff(1)
#     gain = (delta.where(delta > 0, 0)).rolling(window=period).mean()
#     loss = (-delta.where(delta < 0, 0)).rolling(window=period).mean()
#     rs = gain / loss
#     rsi = 100 - (100 / (1 + rs))
#     return rsi


# def calculate_rate_of_change(data: pd.Series, period: int = 25):
#     """
#     Calculate the rate of change (ROC) over a given period (1 minute by default).
#     """
#     return data.diff(period)


# def main():
#     global PREVIOUS_SIGNAL
#     print(f"Starting binary forex bot for {FOREX_PAIR}...")
#     while True:
#         try:
#             # Fetch data
#             data = fetch_forex_data(FOREX_PAIR, TIME_INTERVAL)
#             if data is None:
#                 logging.error("No data received. Retrying...")
#                 time.sleep(60)
#                 continue

#             # Analyze data
#             signal = analyze_forex_data(data)

#             # if PREVIOUS_SIGNAL != signal:
#             logging.info(f"[{datetime.now()}] Signal for {FOREX_PAIR}: {signal}")
#             print(f"[{datetime.now()}] Signal for {FOREX_PAIR}: {signal}\n-------")
#             # Play sound based on signal
#             if signal == "BUY":
#                 subprocess.run(["afplay", "Money.mp3"])  # Play BUY sound
#             elif signal == "SELL":
#                 subprocess.run(["afplay", "Money.mp3"])  # Play SELL sound

#             PREVIOUS_SIGNAL = signal
#             # Wait before the next fetch
#             time.sleep(
#                 30
#             )  # Limit to 1 minute, change if API allows more frequent requests
#         except Exception as e:
#             logging.error(f"An error occurred: {e}")
#             time.sleep(60)


# if __name__ == "__main__":
#     main()


#################################################

# import yfinance as yf
# import subprocess
# import time
# from datetime import datetime
# import pandas as pd
# import logging

# # Forex pair to analyze (e.g., EUR/USD)
# Pair_Input = input("Pair:")
# FOREX_PAIR = Pair_Input + "=X"  # Format for Yahoo Finance forex data

# # Time interval for data (e.g., 1m, 5m, 15m)
# TIME_INTERVAL = "1m"

# # RSI thresholds
# RSI_OVERBOUGHT = 65
# RSI_OVERSOLD = 35

# PREVIOUS_SIGNAL = ""

# # Set up logging
# logging.basicConfig(
#     filename="forex_bot.log", level=logging.INFO, format="%(asctime)s - %(message)s"
# )


# def fetch_forex_data(pair: str, interval: str):
#     """
#     Fetch forex data from Yahoo Finance.
#     """
#     try:
#         # Fetching data for the last 5 days to have more context
#         data = yf.download(pair, interval=interval, period="5d", progress=False)
#         if not data.empty:
#             return data
#         else:
#             logging.error("Error: Data is empty.")
#             return None
#     except Exception as e:
#         logging.error(f"Error fetching data from Yahoo Finance: {e}")
#         return None


# def analyze_forex_data(data):
#     """
#     Analyze forex data and give buy/sell signals based on RSI and rate of change.
#     """
#     df = data.copy()  # Work with the fetched data directly
#     df["RSI"] = calculate_rsi(df["Close"])
#     latest_rsi = df["RSI"].iloc[-1]

#     # Calculate ROC of RSI for 2 minute, 5 minutes, and 10 minutes
#     # df["RSI_ROC_2min_ago"] = calculate_RSI_ROC(df, 2, latest_rsi)
#     df["RSI_ROC_5min_ago"] = calculate_RSI_ROC(df, 7, latest_rsi)
#     df["RSI_ROC_10min_ago"] = calculate_RSI_ROC(df, 15, latest_rsi)

#     latest_rsi_ROC_5min = df["RSI_ROC_5min_ago"].iloc[-7]
#     latest_rsi_ROC_10min = df["RSI_ROC_10min_ago"].iloc[-15]

#     # Calculate ROC for 2 minute, 5 minutes, 10 minutes, and 15 minutes
#     df["ROC_2min"] = calculate_rate_of_change(df["Close"], period=1)
#     df["ROC_5min"] = calculate_rate_of_change(df["Close"], period=5)
#     df["ROC_10min"] = calculate_rate_of_change(df["Close"], period=10)
#     # df["ROC_15min"] = calculate_rate_of_change(df["Close"], period=15)

#     if len(df) < 15:  # Ensure there are enough rows for RSI and ROC calculation
#         logging.warning(
#             "Not enough data to calculate RSI or rate of change. Waiting for more data..."
#         )
#         return "HOLD"

#     latest_close = df["Close"].iloc[-1]
#     latest_ROC_2min = df["ROC_2min"].iloc[-1]
#     latest_ROC_5min = df["ROC_5min"].iloc[-1]
#     latest_ROC_10min = df["ROC_10min"].iloc[-1]
#     # latest_ROC_15min = df["ROC_15min"].iloc[-1]

#     # Debugging logs
#     logging.info(
#         f"Close={latest_close}, RSI={latest_rsi}, ROC_2min={latest_ROC_2min}, ROC_5min={latest_ROC_5min}, "
#     )
#     print(
#         f"Close={latest_close}\n, \nROC_2min={latest_ROC_2min}, "
#         f"\nROC_5min={latest_ROC_5min},\nROC_10min={latest_ROC_10min}"
#         f"\n--, \nRSI={latest_rsi},\nRsi_ROC_5min={latest_rsi_ROC_5min}, {df["RSI"].iloc[-7]}, \nRsi_ROC_10min={latest_rsi_ROC_10min}, {df["RSI"].iloc[-15]}\n",
#     )

#     # Signal logic
#     if latest_rsi < RSI_OVERSOLD:
#         return "HOLD"
#     elif latest_rsi > RSI_OVERBOUGHT:
#         return "HOLD"
#     elif RSI_OVERSOLD < latest_rsi < RSI_OVERBOUGHT:  # RSI between thresholds
#         if (latest_ROC_2min > 0 and latest_ROC_5min > 0) and (
#             latest_rsi_ROC_5min > 0 and latest_rsi_ROC_10min > 0
#         ):
#             return "BUY"
#         elif (latest_ROC_2min < 0 and latest_ROC_5min < 0) and (
#             latest_rsi_ROC_5min < 0 and latest_rsi_ROC_10min < 0
#         ):
#             return "SELL"
#     return "HOLD"  # Default to HOLD if none of the above conditions are met


# def calculate_rsi(data: pd.Series, period: int = 25):
#     """
#     Calculate the Relative Strength Index (RSI).
#     """
#     delta = data.diff(1)
#     gain = (delta.where(delta > 0, 0)).rolling(window=period).mean()
#     loss = (-delta.where(delta < 0, 0)).rolling(window=period).mean()
#     rs = gain / loss
#     rsi = 100 - (100 / (1 + rs))
#     return rsi


# def calculate_RSI_ROC(data, time_frame, latest_rsi):
#     rf = data.copy()
#     RSI_ROC = (latest_rsi - rf["RSI"].iloc[-(time_frame)]) / time_frame
#     # RSI_some_min_ago = calculate_rsi(rf["Close"][:-(time_frame)])
#     # print("rf: ", rf)
#     # print("RSI_some_time: ", RSI_some_min_ago.iloc[-(time_frame) + 1])

#     # # Calculate RSI rate of change based on this data slice
#     return RSI_ROC


# def calculate_rate_of_change(data: pd.Series, period: int = 25):
#     """
#     Calculate the rate of change (ROC) over a given period (1 minute by default).
#     """
#     return data.diff(period)


# def main():
#     global PREVIOUS_SIGNAL
#     print(f"Starting binary forex bot for {FOREX_PAIR}...")
#     while True:
#         try:
#             # Fetch data
#             data = fetch_forex_data(FOREX_PAIR, TIME_INTERVAL)
#             if data is None:
#                 logging.error("No data received. Retrying...")
#                 time.sleep(60)
#                 continue

#             # Analyze data
#             signal = analyze_forex_data(data)

#             # if PREVIOUS_SIGNAL != signal:
#             logging.info(f"[{datetime.now()}] Signal for {FOREX_PAIR}: {signal}")
#             print(f"[{datetime.now()}] Signal for {FOREX_PAIR}: {signal}\n")
#             # Play sound based on signal
#             if signal == "BUY":
#                 subprocess.run(["afplay", "Money.mp3"])  # Play BUY sound
#             elif signal == "SELL":
#                 subprocess.run(["afplay", "Money.mp3"])  # Play SELL sound

#             PREVIOUS_SIGNAL = signal
#             # Wait before the next fetch
#             time.sleep(
#                 30
#             )  # Limit to 1 minute, change if API allows more frequent requests
#         except Exception as e:
#             logging.error(f"An error occurred: {e}")
#             time.sleep(60)


# if __name__ == "__main__":
#     main()
