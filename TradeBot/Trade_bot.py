
import yfinance as yf
import time
from datetime import datetime
import pandas as pd
import logging

# Forex pair to analyze (e.g., EUR/USD)
FOREX_PAIR = 'CADJPY=X'  # Format for Yahoo Finance forex data

# Time interval for data (e.g., 1m, 5m, 15m)
TIME_INTERVAL = '1m'

# RSI thresholds
RSI_OVERBOUGHT = 80
RSI_OVERSOLD = 20

# Set up logging
logging.basicConfig(filename="forex_bot.log", level=logging.INFO, 
                    format="%(asctime)s - %(message)s")

def fetch_forex_data(pair: str, interval: str):
    """  
    Fetch forex data from Yahoo Finance.
    """  
    try:
        # Fetching data for the last 5 days to have more context
        data = yf.download(pair, interval=interval, period="5d")
        if not data.empty:
            return data
        else:
            logging.error("Error: Data is empty.")
            return None
    except Exception as e:
        logging.error(f"Error fetching data from Yahoo Finance: {e}")
        return None

def calculate_rsi(data: pd.Series, period: int = 14):
    """
    Calculate the Relative Strength Index (RSI).
    """
    delta = data.diff(1)
    gain = (delta.where(delta > 0, 0)).rolling(window=period).mean()
    loss = (-delta.where(delta < 0, 0)).rolling(window=period).mean()
    rs = gain / loss
    rsi = 100 - (100 / (1 + rs))
    return rsi

def calculate_rate_of_change(data: pd.Series, period: int = 1):
    """
    Calculate the rate of change (ROC) over a given period (1 minute by default).
    """
    return data.diff(period)

def analyze_forex_data(data):
    """
    Analyze forex data and give buy/sell signals based on RSI and rate of change.
    """
    df = data.copy()  # Work with the fetched data directly
    df['RSI'] = calculate_rsi(df['Close'])
    
    # Calculate ROC for 1 minute, 2 minutes, 5 minutes, and 10 minutes
    df['ROC_1min'] = calculate_rate_of_change(df['Close'], period=1)
    df['ROC_2min'] = calculate_rate_of_change(df['Close'], period=2)
    df['ROC_5min'] = calculate_rate_of_change(df['Close'], period=5)
    df['ROC_10min'] = calculate_rate_of_change(df['Close'], period=10)

    if len(df) < 15:  # Ensure there are enough rows for RSI and ROC calculation
        logging.warning("Not enough data to calculate RSI or rate of change. Waiting for more data...")
        return "HOLD"

    latest_rsi = df['RSI'].iloc[-1]
    latest_close = df['Close'].iloc[-1]
    latest_roc_1min = df['ROC_1min'].iloc[-1]
    latest_roc_2min = df['ROC_2min'].iloc[-1]
    latest_roc_5min = df['ROC_5min'].iloc[-1]
    latest_roc_10min = df['ROC_10min'].iloc[-1]

    # Debugging logs
    logging.info(f"Close={latest_close}, RSI={latest_rsi}, ROC_1min={latest_roc_1min}, ROC_2min={latest_roc_2min}, "
                 f"ROC_5min={latest_roc_5min}, ROC_10min={latest_roc_10min}")
    print(f"DEBUG: Close={latest_close}, RSI={latest_rsi}, ROC_1min={latest_roc_1min}, "
          f"ROC_2min={latest_roc_2min}, ROC_5min={latest_roc_5min}, ROC_10min={latest_roc_10min}")

    # Signal logic
    if latest_rsi < RSI_OVERSOLD and latest_roc_1min > 0 and latest_roc_2min > 0:
        return "BUY"
    elif latest_rsi > RSI_OVERBOUGHT and latest_roc_1min < 0 and latest_roc_2min < 0:
        return "SELL"
    elif RSI_OVERSOLD < latest_rsi < RSI_OVERBOUGHT:  # RSI between thresholds
        if latest_roc_1min > 0 and latest_roc_2min > 0 and latest_roc_5min > 0 and latest_roc_10min > 0:
            return "BUY"
        elif latest_roc_1min < 0 and latest_roc_2min < 0 and latest_roc_5min < 0 and latest_roc_10min < 0:
            return "SELL"
    return "HOLD"  # Default to HOLD if none of the above conditions are met

def main():
    print(f"Starting binary forex bot for {FOREX_PAIR}...")
    while True:
        try:
            # Fetch data
            data = fetch_forex_data(FOREX_PAIR, TIME_INTERVAL)
            if data is None:
                logging.error("No data received. Retrying...")
                time.sleep(60)
                continue
            
            # Analyze data
            signal = analyze_forex_data(data)
            logging.info(f"[{datetime.now()}] Signal for {FOREX_PAIR}: {signal}")
            print(f"[{datetime.now()}] Signal for {FOREX_PAIR}: {signal}")
            
            # Wait before the next fetch (can be reduced if API allows more frequent fetching)
            time.sleep(60)  # Limit to 1 minute, change if API allows more frequent requests
        except Exception as e:
            logging.error(f"An error occurred: {e}")
            time.sleep(60)

if __name__ == "__main__":
    main()
