import pygame
import serial
import sys

# Initialize Pygame
pygame.init()

# Set up the display in full screen
infoObject = pygame.display.Info()
screen_width, screen_height = infoObject.current_w, infoObject.current_h
screen = pygame.display.set_mode((screen_width, screen_height), pygame.FULLSCREEN)
pygame.display.set_caption('Arduino Data Display')

# Define colors and font
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
font_size = screen_height // 20  # Adjust font size for better visibility
font = pygame.font.Font(None, font_size)  # None uses the default font

# Setup Serial Connection
ser = serial.Serial('/dev/ttyACM0', 115200)  # Change this to match your Arduino's serial port

# Variables to store the data
temperature = ''
height = ''
weight = ''
show_summary = False

def draw_text(text, y_offset):
    text_surface = font.render(text, True, WHITE)
    text_rect = text_surface.get_rect(center=(screen_width // 2, screen_height // 2 + y_offset))
    screen.blit(text_surface, text_rect)

# Main loop
running = True
while running:
    screen.fill(BLACK)  # Clear the screen
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:  # Press ESC to exit full screen and close the program
                running = False
            elif event.key == pygame.K_RETURN and show_summary:  # Reset to start new measurements
                show_summary = False
                temperature = ''
                height = ''
                weight = ''

    if not show_summary:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            if 'Temp:' in line:
                temperature = line
            elif 'Height:' in line:
                height = line
            elif 'Weight:' in line:
                weight = line
                show_summary = True  # Trigger summary display after all data has been received

    if show_summary:
        # Display the summary of all measurements
        draw_text(temperature, -font_size * 2)  # Temperature
        draw_text(height, -font_size)           # Height
        draw_text(weight, 0)                    # Weight
    else:
        # Display current or last received values as they come in
        draw_text(line)

    pygame.display.flip()  # Update the display

pygame.quit()
sys.exit()
