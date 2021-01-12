import csv

selected_teams = ['BAL', 'CWS', 'ANA', 'BOS', 'CLE']

weigth = []
heigth = []
age = []

team_list = []
position = []

with open('./mlb_players.csv', mode='r') as csv_file:
    with open('./processed_mlb.csv', 'w') as processed_mlb:
        csv_reader = csv.DictReader(csv_file)
        csv_writer = csv.DictWriter(processed_mlb, csv_reader.fieldnames)

        csv_writer.writeheader()

        for row in csv_reader:
            row['Team'] = row['Team'].strip()

            if row['Team'] in selected_teams:
                if row['Team'] not in team_list:
                    team_list.append(row['Team'])

                row['Position'] = row['Position'].strip().split(' ')[-1].strip()
                if row['Position']  not in team_list:
                    position.append(row['Position'])

                #print(row['Name'])
                row['Weight(lbs)'] = round(float(row['Weight(lbs)']) * 0.453592, 2)
                weigth.append(row['Weight(lbs)'])
                row['Height(inches)'] = round(float(row['Height(inches)']) * 2.54, 2)
                heigth.append(row['Height(inches)'])
                age.append(row['Age'])
                #print(row)
                csv_writer.writerow(row)


        print(f'Menor peso {min(weigth)}')
        print(f'Maior peso {max(weigth)}')
        print(f'Menor altura {min(heigth)}')
        print(f'Maior idade {max(heigth)}')
        print(f'Menor idade {min(age)}')
        print(f'Maior idade {max(age)}')

        print(team_list)
        print(list(dict.fromkeys(position)))
