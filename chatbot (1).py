import re
import sys

def get_response(user_input):
  
    user_input = user_input.lower().strip()
   
    if re.search(r'\b(hi|hello|hey|hola|greetings|morning|evening)\b', user_input):
        return "Greetings. Thank you for reaching out. How may I assist you today?"
    
    
    elif re.search(r'\b(how are you|how\'s it going|how do you do)\b', user_input):
        return "I am functioning at optimal capacity, thank you for inquiring. I hope you are having a productive day. How can I be of service?"
    
    
    elif re.search(r'\b(your name|who are you)\b', user_input):
        return "I am CorporateBot, an automated virtual assistant designed to streamline your inquiries."
    
    elif re.search(r'\b(help|do for me|functions|capabilities)\b', user_input):
        return "I am programmed to process basic inquiries, clarify my core operational parameters, and guide you through this interface."
    
    
    elif re.search(r'\b(bye|goodbye|exit|quit)\b', user_input):
        return "Thank you for your time. Your session has concluded. Have a pleasant day."
    
    
    else:
        return "I apologize, but I am unable to process that request with my current programming. Could you please rephrase or elaborate on your query?"

def start_chatbot():
    print("CorporateBot: System initialized. Please enter your query below. Type 'exit' to terminate the session.")
    print("-" * 65)
    
    while True:
        try:
            user_input = input("You: ")
            
           
            response = get_response(user_input)
            print(f"CorporateBot: {response}")
            
            
            if re.search(r'\b(bye|goodbye|exit|quit)\b', user_input.lower()):
                break
                
        except (KeyboardInterrupt, EOFError):
            print("\nCorporateBot: Session interrupted unexpectedly. Goodbye.")
            sys.exit()

if __name__ == "__main__":
    start_chatbot()