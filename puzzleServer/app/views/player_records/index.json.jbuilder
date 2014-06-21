json.array!(@player_records) do |player_record|
  json.extract! player_record, :id, :player, :score
  json.url player_record_url(player_record, format: :json)
end
