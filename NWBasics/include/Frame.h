#ifndef FRAME_H
#define FRAME_H

#include <string>

class Frame {
 public:
   /**
   * Maximum characters allowed in Frame data.
   */
   static const int MAX_DATA = 64;

   /**
   * The byte appended to the start & end of a serialized frame.
   */
   static const char START_END_BYTE = 0x7E;

  /**
  * An enumeration of distinct frame types.
  */
  enum FrameType : char {ACK, NAK, DATA};

  /**
  * Default Constructor.
  * Creates an empty Frame object.
  */
  Frame();

  /**
  * Constructor.
  * @param data: The Frame data.
  * @param ft: The Frame Type.
  * @param seq: The sequence number.
  * @param source: The source address as a 4-bit char array.
  * @param dest: The destination address as a 4-bit char array.
  * @param evenParityBit: The even-parity bit as a value of 0 or 1.
  */
  Frame(std::string frameData, FrameType ft, char sequence, bool evenParity);

  /**
  * Destructor.
  */
  virtual ~Frame() {}

  /**
  * Deserialize the frame.
  * @param serial: The string to deserialize.
  * @return Returns a Frame created with by the string.
  */
  static Frame deserialize(std::string serial);

  /**
  * Serializes the Frame.
  * @return Returns the Frame as a string.
  */
  std::string serialize();

  /**
  * Checks whether the Frame's even parity bit matches the data.
  * @return Returns True if parity is valid, else False.
  */
  bool parityIsValid();

  /**
  * Set the Frame's data.
  * Cannot exceed MAX_DATA.
  * @param data: The Frame's data.
  */
  void setData(std::string frameData);

  /**
  * Checks the data and finds the correct even-parity bit.
  * @return Returns the correct even-parity bit for the Frame data.
  */
  bool calculateEvenParity();

  /**
  * Sets the Frame's even bit parity.
  */
  void setEvenParity(bool parity) {
    evenParityBit = parity;
  }

  /**
  * Sets the sequence number of the Frame.
  * @param seq: The sequence number.
  */
  void setSeq(char sequence) {
    seq = sequence;
  }

  /**
  * Sets the frame type of the Frame.
  * @param ft: The Frame Type.
  */
  void setFrameType(FrameType ft) {
    frameType = ft;
  }

  /**
  * Gets the frame's data.
  * @return Returns the Frame's data.
  */
  std::string getData() {
    return data;
  }

  /**
  * Gets the Frame's sequence number.
  * @return Returns the sequence number.
  */
  char getSeq() {
    return seq;
  }

  /**
  * Gets the Frame's type.
  * @return Returns the Frame's type.
  */
  FrameType getFrameType() {
    return frameType;
  }

  /**
  * Gets the even parity bit.
  * @return Returns the even parity bit.
  */
  bool getEvenParity() {
    return evenParityBit;
  }

  /**
  * Output stream operator overload.
  * @param os: The output stream.
  * @param frame: The frame.
  */
  friend std::ostream& operator<<(std::ostream& os, const Frame& frame);

  /**
  * Input stream operator overload.
  * @param is: The output stream.
  * @param frame: The frame.
  */
  friend std::istream& operator>>(std::istream& is, const Frame& frame);

 private:
  /**
  * The sequence number.
  */
  char seq;

  /**
  * The frame type.
  */
  FrameType frameType;

  /**
  * The even-parity bit.
  */
  bool evenParityBit;

  /**
  * Source address.
  */
  int sourceAddr;

  /**
  * Destination address.
  */
  int destAddr;

  /**
  * The frame's data.
  * Cannot exceed MAX_DATA.
  */
  std::string data;
};

#endif // FRAME_H
