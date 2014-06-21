class CreatePlayerRecords < ActiveRecord::Migration
  def change
    create_table :player_records do |t|
      t.string :player
      t.integer :score

      t.timestamps
    end
  end
end
