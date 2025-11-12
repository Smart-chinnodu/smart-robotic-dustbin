#!/usr/bin/env python3
"""
Quote Generator for Smart Robotic Dustbin
Manages and provides daily motivational quotes
Author: Ranjith Kumar Veesam
"""

import random
import json
from datetime import datetime

class QuoteGenerator:
    def __init__(self, quotes_file='quotes.json'):
        """
        Initialize quote generator
        
        Args:
            quotes_file: Path to JSON file containing quotes
        """
        self.quotes_file = quotes_file
        self.quotes = self.load_quotes()
        self.daily_quote_index = 0
    
    def load_quotes(self):
        """
        Load quotes from file or use default quotes
        
        Returns:
            List of quote strings
        """
        default_quotes = [
            "Cleanliness is next to godliness!",
            "Be the change you wish to see in the world!",
            "Small actions lead to big impacts!",
            "Keep Earth clean and green!",
            "Reduce, Reuse, Recycle - the 3 Rs of sustainability!",
            "Every piece of waste matters!",
            "Thank you for caring about our planet!",
            "You make a difference every day!",
            "Save Earth, Save our future!",
            "Together we can create a cleaner tomorrow!",
            "Waste segregation is the first step to recycling!",
            "Your small effort creates a huge impact!",
            "Protect nature, it's our only home!",
            "Clean environment, healthy life!",
            "Be a warrior, not a worrier for Earth!",
            "Think green, act green, live green!",
            "The Earth is what we all have in common!",
            "Every day is Earth Day!",
            "Respect nature, respect life!",
            "Plant trees, they give us life!"
        ]
        
        try:
            with open(self.quotes_file, 'r') as f:
                loaded_quotes = json.load(f)
                return loaded_quotes.get('quotes', default_quotes)
        except FileNotFoundError:
            # Create default quotes file
            self.save_quotes({'quotes': default_quotes})
            return default_quotes
    
    def save_quotes(self, data):
        """
        Save quotes to JSON file
        
        Args:
            data: Dictionary containing quotes
        """
        with open(self.quotes_file, 'w') as f:
            json.dump(data, f, indent=2)
    
    def get_random_quote(self):
        """
        Get a random quote from the collection
        
        Returns:
            Random quote string
        """
        return random.choice(self.quotes)
    
    def get_daily_quote(self):
        """
        Get quote of the day (changes daily)
        
        Returns:
            Quote string for today
        """
        # Use date as seed for consistent daily quote
        today = datetime.now().date()
        random.seed(today.toordinal())
        quote = random.choice(self.quotes)
        random.seed()  # Reset seed
        return quote
    
    def get_sequential_quote(self):
        """
        Get quotes in sequential order
        
        Returns:
            Next quote in sequence
        """
        quote = self.quotes[self.daily_quote_index]
        self.daily_quote_index = (self.daily_quote_index + 1) % len(self.quotes)
        return quote
    
    def add_quote(self, new_quote):
        """
        Add a new quote to the collection
        
        Args:
            new_quote: Quote string to add
        """
        if new_quote not in self.quotes:
            self.quotes.append(new_quote)
            self.save_quotes({'quotes': self.quotes})
            return True
        return False
    
    def get_all_quotes(self):
        """
        Get all available quotes
        
        Returns:
            List of all quotes
        """
        return self.quotes.copy()

def main():
    """Test the quote generator"""
    generator = QuoteGenerator()
    
    print("=" * 50)
    print("SMART ROBOTIC DUSTBIN - QUOTE GENERATOR")
    print("=" * 50)
    
    print("\nRandom Quote:")
    print(f"  {generator.get_random_quote()}")
    
    print("\nDaily Quote:")
    print(f"  {generator.get_daily_quote()}")
    
    print("\nSequential Quotes (first 5):")
    for i in range(5):
        print(f"  {i+1}. {generator.get_sequential_quote()}")
    
    print("\nTotal Quotes Available:", len(generator.get_all_quotes()))

if __name__ == "__main__":
    main()
