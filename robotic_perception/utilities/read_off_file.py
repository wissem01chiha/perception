"""

"""
def read_off(file_path):
    points = []
    with open(file_path, 'r') as f:
        lines = f.readlines()
        if lines[0].strip() != 'OFF':
            print("Invalid OFF file")
            return None
        num_points = int(lines[1].split()[0])
        for line in lines[2:2+num_points]:
            coords = line.strip().split()
            points.append([float(coords[0]), float(coords[1]), float(coords[2])])
    return points