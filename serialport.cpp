#include "serialport.h"

bool SerialPort::Open(std::string port_path, int baud_rate)
{
    bool state = false;

    if (IsOpen())
        Close();

    const char* c_port_path = port_path.c_str();
    fd = open(c_port_path, O_RDWR | O_NOCTTY | O_SYNC);

    struct termios tty;
    if (tcgetattr(fd, &tty) < 0) {
        fd = -1;
        state = false;
    }

    if (baud_rate == 9600) {
        cfsetospeed(&tty, (speed_t)B9600);
        cfsetispeed(&tty, (speed_t)B9600);
    } else if(baud_rate == 230400) {
        cfsetospeed(&tty, (speed_t)B230400);
        cfsetispeed(&tty, (speed_t)B230400);
    } else if(baud_rate == 3000000) {
        cfsetospeed(&tty, (speed_t)B3000000);
        cfsetispeed(&tty, (speed_t)B3000000);
    }

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1000;

    if ((tcsetattr(fd, TCSANOW, &tty)) != 0) {
        fd = -1;
        state = false;
    }
    tcflush(fd, TCIFLUSH);
    state = true;

    return state;
}

bool SerialPort::IsOpen()
{
    if (fd >= 0)
        return true;

    return false;
}

void SerialPort::Close()
{
    close(fd);
    fd = -1;
}

void SerialPort::Write(std::vector<char> write_data)
{
    uint size = write_data.size();
    char c_write_data[size];
    for (uint i = 0; i < size; i++)
        c_write_data[i] = write_data.at(i);

    tcflush(fd, TCIFLUSH);
    write(fd, c_write_data, write_data.size());
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    tcdrain(fd);
}

void SerialPort::Write(std::vector<unsigned char> write_data)
{
    unsigned char u_write_data[sizeof(write_data.size())];
    for (uint i = 0; i < write_data.size(); i++)
        u_write_data[i] = write_data.at(i);

    write(fd, u_write_data, write_data.size());
}

std::vector<unsigned char> SerialPort::Read(uint length)
{
    std::vector<unsigned char> read_data;
    unsigned char buffer[length];
    int num_to_read = static_cast<int>(length);
    int read_data_length = 0;
    int total_read = 0;

    int error_data_count = 0;
    int error_usb_count = 0;

    while (num_to_read > 0) {
        read_data_length = read(fd, &buffer[total_read], num_to_read);
        if (read_data_length > 0) {
            total_read += read_data_length;
            num_to_read -= read_data_length;
        }

        if (read_data_length == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(1000));
            error_data_count++;
        } else if(read_data_length == -1) {
            std::this_thread::sleep_for(std::chrono::microseconds(1000));
            error_usb_count++;
        }

        if (error_data_count == error_count || error_usb_count == error_count) {
            if (error_data_count == error_count)
                read_data.push_back(error_data_code);
            if (error_usb_count == error_count)
                read_data.push_back(error_usb_code);

            break;
        }
    }

    if (read_data.size() == 0) {
        for (uint i = 0; i < length; i++)
            read_data.push_back(buffer[i]);
    }

    return read_data;
}

std::vector<unsigned char> SerialPort::Read(uint length, uint break_code)
{
    std::vector<unsigned char> read_data;
    unsigned char buffer[length];
    int num_to_read = static_cast<int>(length);
    int read_data_length = 0;
    int total_read = 0;

    int error_data_count = 0;
    int error_usb_count = 0;

    while (num_to_read > 0) {
        read_data_length = read(fd, &buffer[total_read], num_to_read);

        if (read_data_length > 0) {
            total_read += read_data_length;
            num_to_read -= read_data_length;
        }

        if (read_data_length == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(1000));
            error_data_count++;
        } else if(read_data_length == -1) {
            std::this_thread::sleep_for(std::chrono::microseconds(1000));
            error_usb_count++;
        }

        if (error_data_count == error_count || error_usb_count == error_count) {
            if (error_data_count == error_count)
                read_data.push_back(error_data_code);
            if (error_usb_count == error_count)
                read_data.push_back(error_usb_code);

            break;
        }

        if (buffer[total_read - 1] == static_cast<unsigned char>(break_code))
            break;
    }

    if (read_data.size() == 0) {
        for (uint i = 0; i < length; i++)
            read_data.push_back(buffer[i]);
    }

    return read_data;
}

std::vector<unsigned char> SerialPort::Read(uint length, unsigned char first_byte)
{
    std::vector<unsigned char> read_data;
    unsigned char buffer[length];
    int num_to_read = static_cast<int>(length);
    int read_data_length = 0;
    int total_read = 0;

    while (num_to_read > 0) {
        read_data_length = read(fd, &buffer[total_read], num_to_read);

        if (read_data_length > 0 && buffer[0] == first_byte) {
            total_read += read_data_length;
            num_to_read -= read_data_length;
        }
    }

    for (uint i = 0; i < length; i++)
        read_data.push_back(buffer[i]);

    return read_data;
}
