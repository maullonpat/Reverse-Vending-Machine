import tensorflow as tf

# Load the TFLite model
interpreter = tf.lite.Interpreter(model_path="model.tflite")
interpreter.allocate_tensors()

# Get input and output details
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()

# Perform inference, assuming input_data is your input tensor
interpreter.set_tensor(input_details[0]['index'], input_data)
interpreter.invoke()

# Get the output tensor
output_data = interpreter.get_tensor(output_details[0]['index'])

# Now you can use the output_data for further processing