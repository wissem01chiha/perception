import csv

def load_points(file_path):
    """
    Load points from a file.

    Args:
        file_path (str): The path to the file containing points.

    Returns:
        list: A list of points loaded from the file. Each point is represented
              as a list of three floats [x, y, z].

    Raises:
        FileNotFoundError: If the specified file_path does not exist.
        ValueError: If the file is not in a supported format or has invalid content.

    Example:
        >>> load_points('points.csv')
        [[1.0, 2.0, 3.0], [4.0, 5.0, 6.0], [7.0, 8.0, 9.0]]
    """
    points = []
    try:
        with open(file_path, 'r') as f:
            file_extension = file_path.split('.')[-1].lower()
            if file_extension == 'off':
                lines = f.readlines()
                if lines[0].strip() != 'OFF':
                    raise ValueError("Invalid OFF file")
                num_points = int(lines[1].split()[0])
                for line in lines[2:2+num_points]:
                    coords = line.strip().split()
                    points.append([float(coords[0]), float(coords[1]), float(coords[2])])
            elif file_extension == 'csv':
                csv_reader = csv.reader(f)
                for row in csv_reader:
                    try:
                        points.append([float(row[0]), float(row[1]), float(row[2])])
                    except ValueError:
                        raise ValueError("Error parsing CSV file")
            else:
                raise ValueError("Unsupported file type")
    except FileNotFoundError:
        raise FileNotFoundError(f"File '{file_path}' not found")
    return points


