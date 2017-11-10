class Transmitter {
protected:
public:
    Transmitter();
    ~Transmitter();
    void getSensorValues(short int* sensor);
    void testParser();
    void parseBuffer();
    void printBuffer(char* buffer, int size);
    void sendData();

private:
    char msg_buffer[11];
    short int pitch, yaw, roll, altitude;
    unsigned char checkSum(char* in, int size);
};