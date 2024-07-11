import socket
import threading

# Server address and port
SERVER_ADDRESS = '127.0.0.1'
SERVER_PORT = 5000
NUM_CONNECTIONS = 500
MESSAGE = "Hello from client {}"

def connect_and_send_message(client_id):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect((SERVER_ADDRESS, SERVER_PORT))
            message = MESSAGE.format(client_id)
            print(f"Client {client_id} sending: {message}")
            sock.sendall(message.encode())
            data = sock.recv(1024)
            print(f"Client {client_id} received: {data.decode()}")
    except Exception as e:
        print(f"Client {client_id} encountered an error: {e}")

def main():
    threads = []

    for i in range(NUM_CONNECTIONS):
        thread = threading.Thread(target=connect_and_send_message, args=(i,))
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()

if __name__ == "__main__":
    main()
