print("Hello world!")

def simulate(input_queues, output_queues, ready_queue, check_queue, max_ticks, array_dim): 
    print("Will compute", array_dim, "for", max_ticks, "cycles..")
    inputs = input_queues[0]
    outputs = output_queues[0]
    ready = ready_queue[0]
    # input arguments come as tuples, even though a 6 item tuple was sent from C
    # make the stupid tuples, lists

    for i, item in enumerate(outputs):
        if ready[i]:
            outputs[i] = item + inputs[i]
    
    return outputs
